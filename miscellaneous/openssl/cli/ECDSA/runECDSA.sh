#! /bin/bash

for i in {1..2000} ; do 
	/home/tam/Desktop/bignum/openssl/apps/openssl dgst -sha256 -sign ecdsa_priv.pem -out signature.txt plain.txt
done
