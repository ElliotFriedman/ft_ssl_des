rm -rf ft_ssl.dSYM/Contents
rm -rf ft_ssl.dSYM
rm ._Make*
rm .DS_Store
make fclean
make clean
git add .
git commit -m "${1}"
git push github master
git push origin master
echo "




DONE!

pushed with commit message: \"${1}\"


"
