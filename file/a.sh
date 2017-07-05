for i in `ls *.txt`
do
    cat $i | awk -F'\t' '{print $1, "\t", $2, "\t" "'"$i"'"}'
done
