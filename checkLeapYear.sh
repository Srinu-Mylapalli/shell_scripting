echo "enter year"
read year
n=`expr $year % 4`
if [ $n -eq 0 ]
then
        echo "leap year: $year"
else
        echo "not leap year: $year"
fi
