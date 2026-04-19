from Crypto.Cipher import AES
from Crypto.Util import Counter
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes

def print_info(plaintext, ciphertext, decrypted_text, iv_nonce=None):
    # print()
    print("="*100)
    print(f"Plaintext       :   {plaintext}")
    print(f"IV/Nonce(hex)   :   {iv_nonce.hex() if iv_nonce is not None else 'N/A'}")
    print(f"Ciphertext(hex) :   {ciphertext.hex()}")
    print(f"Decrypted (hex) :   {decrypted_text}")
    print("="*100)
    
def ctr(plaintext, key, nonce):
    print(f"\n=== CTR Mode Operation ===")
    
    nonce_8bytes = nonce[:8] # take first 8 bytes
    
    ctr_enc = Counter.new(64, prefix=nonce_8bytes, initial_value=0)
    ctr_dec = Counter.new(64, prefix=nonce_8bytes, initial_value=0)
    
    cipher_enc = AES.new(key, AES.MODE_CTR, counter=ctr_enc)
    ciphertext = cipher_enc.encrypt(plaintext)
    
    cipher_dec = AES.new(key, AES.MODE_CTR, counter=ctr_dec)
    decrypted_text = cipher_dec.decrypt(ciphertext)
    
    print_info(plaintext, ciphertext, decrypted_text, nonce)
    
    return ciphertext, decrypted_text 
    
    
def ofb(plaintext, key, nonce):
    print(f"\n=== OFB Mode Operation ===")
    
    cipher_enc = AES.new(key, AES.MODE_OFB, nonce)
    ciphertext = cipher_enc.encrypt(plaintext)
    
    cipher_dec = AES.new(key, AES.MODE_OFB, nonce)
    decrypted_text = cipher_dec.decrypt(ciphertext)
    
    print_info(plaintext, ciphertext, decrypted_text, nonce)
    
    return ciphertext, decrypted_text 
    
    
def cfb(plaintext, key, iv, s_bytes):
    print(f"\n=== CFB Mode Operation ===")
    
    cipher_enc = AES.new(key, AES.MODE_CFB, iv, segment_size=s_bytes*8)
    ciphertext = cipher_enc.encrypt(plaintext)
    
    cipher_dec = AES.new(key, AES.MODE_CFB, iv, segment_size=s_bytes*8)
    decrypted_text = cipher_dec.decrypt(ciphertext)
    
    print_info(plaintext, ciphertext, decrypted_text, iv)
    
    return ciphertext, decrypted_text 
    
    
def cbc(plaintext, key, iv):
    print(f"\n=== CBC Mode Operation ===")
    
    cipher_enc = AES.new(key, AES.MODE_CBC, iv)
    padded_text = pad(plaintext, AES.block_size)
    ciphertext = cipher_enc.encrypt(padded_text)
    
    cipher_dec = AES.new(key, AES.MODE_CBC, iv)
    decrypt_padded = cipher_dec.decrypt(ciphertext)
    decrypted_text = unpad(decrypt_padded, AES.block_size)
    
    print_info(plaintext, ciphertext, decrypted_text, iv)
    
    return ciphertext, decrypted_text 

def ecb(plaintext, key):
    print(f"\n=== ECB Mode Operation ===")
    
    cipher_enc = AES.new(key, AES.MODE_ECB)
    padded_text = pad(plaintext, AES.block_size)
    ciphertext = cipher_enc.encrypt(padded_text)
    
    
    cipher_dec = AES.new(key, AES.MODE_ECB)
    decrypt_padded = cipher_dec.decrypt(ciphertext)
    decrypted_text = unpad(decrypt_padded, AES.block_size)
    
    print_info(plaintext, ciphertext, decrypted_text)
    
    return ciphertext, decrypted_text

def main():
    print("=== Bock Operation Mode ===")
    
    plaintext = b"ADMINISTRATOR   ADMINISTRATOR"
    
    key = get_random_bytes(16)
    
    iv_nonce = get_random_bytes(16) # AES block size is 16 bytes
    
    s_bytes = 16
    
    ecb(plaintext, key)
    cbc(plaintext, key, iv_nonce)
    cfb(plaintext, key, iv_nonce, s_bytes)
    ofb(plaintext, key, iv_nonce)
    ctr(plaintext, key, iv_nonce)
    

if __name__ == '__main__':
    main()