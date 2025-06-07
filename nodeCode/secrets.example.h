/**
 * @file secrets.example.h
 * @brief Example template for LoRaWAN secrets and application identifiers.
 *
 * @details
 * This file serves as a template for `secrets.h`, which stores the LoRaWAN
 * device and application identifiers necessary for network communication.
 *
 * TO USE:
 * 1. Copy this file and rename the copy to `secrets.h`.
 * 2. Open `secrets.h` and replace the placeholder values for `JOINEUI`,
 *    `DEVEUI`, and `APPKEY` with the actual values provided by your
 *    LoRaWAN Network Server (e.g., The Things Network console, The Things Stack).
 * 3. **Important**: Ensure that `secrets.h` (the file with your actual keys)
 *    is listed in your project's `.gitignore` file to prevent your private
 *    keys from being committed to a version control repository.
 *
 * @author Project Contributors
 * @date 2024-03-15
 * @version 1.0
 */

#define JOINEUI "0000000000000000"      ///< \brief Placeholder for JoinEUI (EUI-64, MSB). Replace with your value from the LoRaWAN Network Server.
#define DEVEUI  "0000000000000000"      ///< \brief Placeholder for DevEUI (EUI-64, MSB). Replace with your device-specific EUI.
#define APPKEY  "00000000000000000000000000000000" ///< \brief Placeholder for AppKey (128-bit AES key, MSB). Replace with your application-specific key.