#//take output of openssl and put it into this converter to turn base64 to bytes:
#//https://cryptii.com/base64-to-hex

while :
	do
	openssl enc -des-ecb  -pass pass:"hello" -iv 00 -nosalt -in main.c

	echo "


	"
	sleep 1
	./ft_ssl des main.c
done
