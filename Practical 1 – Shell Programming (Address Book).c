
#!/bin/bash

BOOK="address_book.txt"

while true
do
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert Record"
    echo "4. Delete Record"
    echo "5. Modify Record"
    echo "6. Exit"

    read -p "Enter choice: " choice

    case $choice in
        1)
            > "$BOOK"
            echo "Address Book Created"
            ;;

        2)
            if [ -f "$BOOK" ]; then
                cat "$BOOK"
            else
                echo "Address Book does not exist"
            fi
            ;;

        3)
            read -p "Enter Name: " name
            read -p "Enter Phone: " phone
            read -p "Enter Email: " email

            echo "$name|$phone|$email" >> "$BOOK"
            echo "Record Inserted"
            ;;

        4)
            read -p "Enter Name to Delete: " name

            if grep -iq "^$name|" "$BOOK"; then
                grep -iv "^$name|" "$BOOK" > temp.txt
                mv temp.txt "$BOOK"
                echo "Record Deleted"
            else
                echo "Record Not Found"
            fi
            ;;

        5)
            read -p "Enter Name to Modify: " name

            if grep -iq "^$name|" "$BOOK"; then
                grep -iv "^$name|" "$BOOK" > temp.txt
                mv temp.txt "$BOOK"

                read -p "Enter New Name: " name
                read -p "Enter New Phone: " phone
                read -p "Enter New Email: " email

                echo "$name|$phone|$email" >> "$BOOK"
                echo "Record Modified"
            else
                echo "Record Not Found"
            fi
            ;;

        6)
            echo "Exiting..."
            exit
            ;;

        *)
            echo "Invalid Choice"
            ;;
    esac
done
