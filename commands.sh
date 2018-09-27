echo "

	CBC pass: ${1}
	in main.c

"

openssl enc -des-cbc -pass pass:"${1}" -nosalt -in main.c

echo "

	ECB pass: ${1}
	in main.c
   
"

openssl enc -des-ecb -pass pass:"${1}" -in main.c -out testog

# openssl enc -des -pass pass:MYPASSWORD -P -S 2F6760E3D7713CBA

#echo  "56aWZJGAybc=" | openssl enc -des -d -a -pass pass:"hello" -nosalt 
#echo " " | openssl enc -des-cbc -e -a -pass pass:"hello" -nosalt


# -A                 Process base64 data on one line (requires -a)
# -a                 Perform base64 encoding/decoding (alias -base64)
# -bufsize size      Specify the buffer size to use for I/O
# -d                 Decrypt the input data
# -debug             Print debugging information
# -e                 Encrypt the input data (default)
# -engine id         Use the engine specified by the given identifier
# -in file           Input file to read from (default stdin)
# -iv IV             IV to use, specified as a hexidecimal string
# -K key             Key to use, specified as a hexidecimal string
# -md digest         Digest to use to create a key from the passphrase
# -none              Use NULL cipher (no encryption or decryption)
# -nopad             Disable standard block padding
# -out file          Output file to write to (default stdout)
# -P                 Print out the salt, key and IV used, then exit
#                      (no encryption or decryption is performed)
#
# -p                 Print out the salt, key and IV used
# -pass source       Password source
# -S salt            Salt to use, specified as a hexidecimal string
# -salt              Use a salt in the key derivation routines (default)
# -v                 Verbose


#		Flags I Have to be Concerned About

# DONE -a, decode/encode the input/output in base64, depending on the encrypt mode

# DONE -d, decrypt mode

# DEFAULT -e, encrypt mode (default)

# -i, input file for message

# NEED TO CHECK ENDIANNESS -k, key in hex is the next arguement.
#	(Behave like openssl des -K not openssl des -k)
#
# -o, output file for message

# -p, password in ascii is the next argument.
#(Behave like a modifiedd openssl des -pass not like openssl des -p or -P) (A verbose explanation is given in the next section)

# -s, the salt in hex is the next argument. (Behave like openssl des -S)

# -v, initialization vector in hex is the next argument. (Behave like openssl des -iv not openssl des -v)


#Make a function to grab all arguments
#		-Store args as global variables
#		-g_vars == 10x easier than structs
