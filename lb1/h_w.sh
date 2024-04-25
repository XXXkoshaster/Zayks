#!/bin/bash
case "$#" in
    0)
        echo "Print arguments: key, key_value, file_name, prefix:"
        read KEY KEY_VALUE FILE_NAME PREFIX ;;
    1)
        KEY="-l"
        KEY_VALUE=1000
        FILE_NAME=$1
        PREFIX="x" ;;
    2)
        KEY="-l"
        KEY_VALUE=1000
        FILE_NAME=$1
        PREFIX=$2 ;;
    3)
        KEY=$1
        KEY_VALUE=$2
        FILE_NAME=$3
        PREFIX="x" ;;
    4)
        KEY=$1
        KEY_VALUE=$2
        FILE_NAME=$3
        PREFIX=$4 ;;
    *)
        echo "Error. Too many arguments"
        exit 1 ;;
esac

if [ ! -f "$FILE_NAME" ]; then
    echo "Error.  $FILE_NAME: file not found"
    exit 1
fi

case $KEY in
    -l)
        TOTAL_ELEMENTS=$(wc -l < "$FILE_NAME")
        
        (( FILES_NEEDED = (TOTAL_ELEMENTS + KEY_VALUE - 1) / KEY_VALUE ))
        
        END_LINE=$KEY_VALUE
        ;;
    -b)
        TOTAL_ELEMENTS=$(wc -c < "$FILE_NAME")
        
        (( FILES_NEEDED = (TOTAL_ELEMENTS + KEY_VALUE - 1) / KEY_VALUE ))
        
        END_LINE=$KEY_VALUE
        ;;
    -n) 
        TOTAL_ELEMENTS=$(wc -c < "$FILE_NAME")
        
        FILES_NEEDED=$KEY_VALUE
        
        ((END_LINE = TOTAL_ELEMENTS / KEY_VALUE))
        ;;
    *)
        echo "Error. $KEY: unexpecte value"
        ;;
esac

for (( FILE_NUMBER=1; FILE_NUMBER<=FILES_NEEDED; FILE_NUMBER++ ))
do
    OUTPUT_FILE="${PREFIX}${FILE_NUMBER}.txt"
    case "$KEY" in
        -l)
            if [ $TOTAL_ELEMENTS -lt $KEY_VALUE ]; then
                head -n "$END_LINE" "$FILE_NAME" | tail -n "$TOTAL_ELEMENTS" > "$OUTPUT_FILE"
            else 
                head -n "$END_LINE" "$FILE_NAME" | tail -n "$KEY_VALUE" > "$OUTPUT_FILE"
            fi
            ((TOTAL_ELEMENTS -= KEY_VALUE))
            ((END_LINE += KEY_VALUE))  
            ;;
        -b)
            if [ $TOTAL_ELEMENTS -lt $KEY_VALUE ]; then
                head -c "$END_LINE" "$FILE_NAME" | tail -c "$TOTAL_ELEMENTS" > "$OUTPUT_FILE"
            else 
                head -c "$END_LINE" "$FILE_NAME" | tail -c "$KEY_VALUE" > "$OUTPUT_FILE"
            fi
            ((TOTAL_ELEMENTS -= KEY_VALUE))
            ((END_LINE += KEY_VALUE))  
            ;;
        -n)
            if [ $FILE_NUMBER -eq $FILES_NEEDED ]; then
                tail -c $(( TOTAL_ELEMENTS - (FILE_NUMBER - 1) * END_LINE )) "$FILE_NAME" > "$OUTPUT_FILE"
            else
                head -c $(( FILE_NUMBER * END_LINE )) "$FILE_NAME" | tail -c $END_LINE > "$OUTPUT_FILE"
            fi
            ;;
    esac   
    echo "File created: $OUTPUT_FILE"
done