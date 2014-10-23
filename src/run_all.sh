for f in *.o; do
  echo $f
  ./$f
  echo ""
  echo "-----"
done
