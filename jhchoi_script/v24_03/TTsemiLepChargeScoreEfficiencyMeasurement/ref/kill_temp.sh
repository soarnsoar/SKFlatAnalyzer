for i in {80..114}; do
    echo $i
    kill %"${i}"
done
