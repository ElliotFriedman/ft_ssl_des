
#this works
echo " " | openssl des-cbc -a -e -K  6162636461626364 -iv 0011223344556677

echo "zqYWONX68rWNxl7msIdGC67Uh2HfVEBo" | openssl des-cbc -d -a -K 6162636461626364 -iv 0011223344556677


#this won't work because we are not using base64 encoding so reading the output is next to impossible
#echo "zqYWONX68rWNxl7msIdGC67Uh2HfVEBo" | openssl des-cbc -d  -K 6162636461626364 -iv 0011223344556677
#remember -a or you get raw bytes as the output that are hard to work with
#echo "one deep secret" | openssl des-cbc  -e -K  6162636461626364 -iv 0011223344556677
