
# Assignment 1b
clear 
CREATE()
{
	echo "Enter name of the Address book"
	read name
	
	result=`ls | grep $name | wc -w`
	
	if [ $result -gt 0 ]
	then
		echo "File already exists!"
	else
		touch $name
		echo "File created!"
	fi
}


DISPLAY() 
{
	#echo "Enter the file you want to open"
	#read $name
	result=`ls | grep $name | wc -w`
	
	if [ $result -gt 0 ]
	then
		cat $name
	else
		echo "File does not exists!"
	fi
}

INSERT()
{
	#echo "Enter the file you want to open"
	#read $name
	
	result=`ls | grep $name | wc -w`
	
	if [ $result -gt 0 ]
	then
		echo "Enter email"
		read email
		len=`cat $name | grep $email | wc -w`
		if [ $len -gt 0 ]
		then 
			echo "Record already exists"
		else
			echo "Enter first name, last name, mobile number"
			read fname lname mobno
			record=`echo $fname $lname $email $mobno`
			
			echo $record >> $name # > -- override
			echo "Record Inserted!"
		fi
	else
		echo "File does not exists!"
	fi
}

MODIFY()
{
	#echo "Enter the file you want to open"
	#read $name
	
	result=`ls | grep $name | wc -w`
	
	if [ $result -gt 0 ]
	then
		echo "Enter email"
		read email
		len=`cat $name | grep $email | wc -w`
		if [ $len -gt 0 ]
		then 
			echo "Enter modified first name, last name, mobile no"
			read fname lname mobno
			new=`echo $fname $lname $email $mobno`
			old=`cat $name | grep $email`
			
			echo "Old record : $old"
			echo "New Record : $new"
			sed -i s/"$old"/"$new"/g $name
			echo "Record modified"
		else
			echo "Enter first name, last name, mobile number"
			read fname lname mobno
			record=`echo $fname $lname $email $mobno`
			
			echo $record >> $name # > -- override
			echo "Record Inserted!"
		fi
	else
		echo "File does not exists!"
	fi
}

DELETE()
{
	#echo "Enter the file you want to open"
	#read $name
	
	result=`ls | grep $name | wc -w`
	
	if [ $result -gt 0 ]
	then
		echo "Enter email"
		read email
		len=`cat $name | grep $email | wc -w`
		if [ $len -gt 0 ]
		then 
			old=`cat $name | grep $email`
			
			sed -i s/"$old"//g $name
			sed -i /^$/d $name
			echo "Record DELETED"
		else
			echo "Record Not Found"
		fi
	else
		echo "File does not exists!"
	fi
}

SEARCH()
{
	#echo "Enter the file you want to open"
	#read $name
	
	result=`ls | grep $name | wc -w`
	
	if [ $result -gt 0 ]
	then
		echo "Enter email"
		read email
		len=`cat $name | grep $email | wc -w`
		if [ $len -gt 0 ]
		then 
			rec=`cat $name | grep $email`
			
			echo "Record Found"
			echo "$rec"
		else
			echo "Record Not Found"
		fi
	else
		echo "File does not exists!"
	fi
}
while [ true ]
do
	echo "******************MENU******************"
	echo "1] Create"
	echo "2] Display"
	echo "3] Insert record"
	echo "4] Modify record"
	echo "5] Delete record"
	echo "6] Search record"
	echo "7] Exit"
	
	echo "Enter Choice"
	read choice
	
	case $choice in
	
		1)CREATE ;;
		2)DISPLAY ;;
		3)INSERT ;;
		4)MODIFY ;;
		5)DELETE ;;
		6)SEARCH ;;
		7) exit ;;
		
		*) echo "Wrong choice" ;;
		
	esac
done	
	
