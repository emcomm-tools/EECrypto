# EECrypto

Symmetric text encryption tool using the EECrypto algorithm. Cipher and decipher text messages using a shared passphrase.

Part of the [EmComm-Tools](https://github.com/emcomm-tools/debian-dev) project, where it ships as **ET-Crypto**.

## What It Does

EECrypto takes plain text and a passphrase, and produces a hex-encoded cipher text. The same passphrase deciphers the text back to its original form. The algorithm is symmetric — the same key is used for both encryption and decryption.

### The Algorithm

- **Key derivation**: The passphrase is processed character by character through a cycle of 6 operations (OR, ADD, SUB, MUL, DIV, XOR) with bit shifts, producing a 64-bit seed. The seed is then XORed with 4 key tables (256 entries each) to generate a 256-element key array.
- **Encryption**: Plain text is processed backwards in 4-character blocks. Each block is XOR-mixed into a 64-bit value, then XORed with the key and 4 substitution boxes (S-boxes). The result is output as 16-character hex strings.
- **Decryption**: The reverse process. A magic number (60960) embedded in the cipher text validates that the correct passphrase was used.
- **S-boxes and key tables**: 8 lookup tables of 256 x 64-bit values each (2,048 constants total), providing the non-linearity of the cipher.

## History

EECrypto was originally developed by Sylvain Deguire (VA2OPS) as a personal encryption project:

1. **mobilEEnigma** — First published on BlackBerry (Java), then ported to iPhone 3 (Objective-C) and Android that same year
2. **officEEnigma** — Desktop version for macOS, Windows and Linux
3. **ET-Crypto** (2026) — Native Linux C++/Qt5 port for the EmComm-Tools project

The core algorithm and all S-box/key table constants have remained identical across all versions, ensuring cross-compatibility — text ciphered on any version can be deciphered on any other.

## Building

### Prerequisites

```bash
sudo apt install qtbase5-dev cmake g++
```

### Compile

```bash
mkdir -p build && cd build
cmake ..
make
```

### Run

```bash
./et-crypto
```

## Usage

1. Enter a passphrase
2. Type or paste text in the text area
3. Click **Cipher** to encrypt (cipher text is also copied to clipboard)
4. Click **Decipher** to decrypt (using the same passphrase)
5. Click **Clear** to wipe all fields and clipboard

## Amateur Radio Usage

Amateur Radio regulations in Canada (Industry Canada RBR-4) and the United States (FCC Part 97) prohibit transmitting encrypted communications intended to obscure their meaning.

When using ET-Crypto over RF, operators **must**:

- Publish their passphrase openly
- Comply with all applicable laws and regulations

### Recommended Practice

Use the **destination station's callsign** as the passphrase. This ensures:

- The passphrase is inherently public (callsigns are public record)
- Any licensed amateur can decipher the message by knowing the recipient
- Full compliance with regulations requiring transmissions not to obscure meaning

## License

MIT License — see [LICENSE](LICENSE) for details.

## Author

**Sylvain Deguire (VA2OPS)**

73!
