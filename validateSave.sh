#!/bin/bash
PREFIX_PATH=""
ACTION=""
OLD_PATH=""
SLOT=""
HASH=""
HASH_CHECK=""
which md5sum >> /dev/null
if [ $? -ne 0 ]
then
    echo "This script needs md5sum to function"
    exit 1
fi
if [ $# -ne 3 ]
then
    if [ $# -eq 0 ]
    then
        echo "Did you know that args are also supported? Arg usage: validateSave.sh (pfx path) (repair|validate) (saveslot)"
        echo "Please write the path to the Wine prefix used by the Neptunia Re;birth 1 software: (without ending with a slash)"
        read PREFIX_PATH
        PREFIX_PATH=${PREFIX_PATH}"/drive_c/users/steamuser/My Documents/My Games/Idea Factory International, Inc/Hyperdimension Neptunia Re;Birth1"
        echo "What action do you wish to perform? (repair|validate)"
        read ACTION
        echo "What slot should be validated? (number i.e 0003 for slot 3 and no more than 4 numbers, So 23 would be 0023)"
        read SLOT
        if [ "$ACTION" == "repair" ] || [ "$ACTION" == "validate" ]
        then
            OLD_PATH=$(pwd)
            if [ "$ACTION" == "repair" ]
            then
                OLD_PATH=$(pwd)
                FILE_PATH=${PREFIX_PATH}"/data"
                FILE_PATH=${FILE_PATH}"$SLOT"
                FILE_SLOT_PATH=${FILE_PATH}
                FILE_PATH=${FILE_PATH}".sav"
                FILE_SLOT_PATH=${FILE_SLOT_PATH}".savslot"
                stat "$FILE_PATH" >> /dev/null
                if [ $? -ne 0 ]
                then
                    echo "Could not access the slot"
                    exit 1
                else
                    stat "$FILE_SLOT_PATH" >> /dev/null
                    if [ $? -ne 0 ]
                    then
                        echo "Could not access the slot"
                        exit 1
                    else
                        rm ./hash.txt >> /dev/null
                        echo -ne $(echo $(md5sum "$FILE_PATH" | awk '{ print $1 }' | sed -e 's/../\\x&/g')) >> ./hash.txt
                        dd if=./hash.txt seek=24 count=16 of="$FILE_SLOT_PATH" oflag=seek_bytes iflag=skip_bytes,count_bytes bs=1 status=none conv=notrunc
                        echo "Saveslot patched!"
                        exit 0
                    fi
                fi
            else
                OLD_PATH=$(pwd)
                FILE_PATH=${PREFIX_PATH}"/data"
                FILE_PATH=${FILE_PATH}"$SLOT"
                FILE_SLOT_PATH=${FILE_PATH}
                FILE_PATH=${FILE_PATH}".sav"
                FILE_SLOT_PATH=${FILE_SLOT_PATH}".savslot"
                stat "$FILE_PATH" >> /dev/null
                if [ $? -ne 0 ]
                then
                    echo "Could not access the slot"
                    exit 1
                else
                    stat "$FILE_SLOT_PATH" >> /dev/null
                    if [ $? -ne 0 ]
                    then
                        echo "Could not access the slot"
                        exit 1
                    else
                        dd if="$FILE_SLOT_PATH" skip=24 count=16 of=./hash.txt iflag=skip_bytes,count_bytes bs=1 status=none
                        HASH=$(cat ./hash.txt | (od -vt x1|awk '{$1="";print}'))
                        HASH="${HASH//[[:blank:]]/}"
                        #echo $HASH
                        HASH_CHECK=$(md5sum "$FILE_PATH" | awk '{ print $1 }')
                        #echo $HASH_CHECK
                        if [ "$HASH_CHECK" == "$HASH" ]
                        then
                            echo "The save file is correctly hashed!"
                            exit 0
                        else
                            echo "Savefile hash validation failed!"
                            exit 1
                        fi
                    fi
                fi
            fi
        else
            echo "Invalid input"
            exit 1
        fi

    else
        echo "Usage: validateSave.sh (pfx path) (repair|validate) (saveslot) OR just run validateSave.sh"
    exit 1
    fi
fi
    