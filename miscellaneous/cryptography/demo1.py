from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives.asymmetric import utils

private_key = ec.generate_private_key(
    ec.SECP256R1()
)

data = b"this is some data I'd like to sign"

signature = private_key.sign(
    data,
    ec.ECDSA(hashes.SHA256())
)

sig=utils.decode_dss_signature(signature)
print(len(hex(sig[0])))