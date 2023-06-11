import { createCipheriv, CipherGCMTypes } from "crypto";

const algorithm: CipherGCMTypes = 'aes-256-gcm',
    args = () => [
        process.env.KEY, 
        process.env.IV
    ] as [Buffer, Buffer];

/**
 * Encrypt a string using prepared key and iv
 * @param str 
 */
export function encrypt(str: string) {
    const cipher = createCipheriv(algorithm, ...args());
    return Buffer.concat([cipher.update(str), cipher.final()]).toString('hex');
}

/**
 * Decrypt a string using prepared key and iv
 * @param str 
 */
export function decrypt(str: string) {
    const cipher = createCipheriv(algorithm, ...args());
    return Buffer.concat([cipher.update(str), cipher.final()]).toString('hex');
}