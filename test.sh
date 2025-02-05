echo "Running tests..."
echo

output=$(./cmpe351 -t 2 -f input.txt  -o output.txt)

if [ $? -eq 0 ] ; then
  echo "Pass: Program exited zero"
else
  echo "Fail: Program did not exit zero"
  exit 1
fi

nl=$(wc -l output.txt| cut -f1 -d " ")

if [ $nl -eq 6 ] ; then
  echo "Pass: Number of lines in output seem OK!"
else
  echo "Number of lines in output not OK!"
  exit 1
fi

echo
echo "Simple tests OK!"

exit 0
