ARR_FILES=($(ls wrong_etabin_in_SLT/*.root))

for THIS_FILE in ${ARR_FILES[@]};do
    python3 Fix__ProjectionY_To_SLT.py ${THIS_FILE}
done

		 

