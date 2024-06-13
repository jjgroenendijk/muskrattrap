function decodeUplink(input) {
    var bytes = input.bytes;
    var data = {};
    
    // Decode 'id' from the first 4 bytes
    // The 'id' is a 32-bit integer formed by combining bytes 0 to 3
    data.id = ((bytes[0] << 24) >>> 0) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3];
    
    // Decode 'version' from the 5th byte
    // The 'version' is a single byte indicating the version of the payload
    data.version = bytes[4];
    
    // Decode 'doorStatus', 'catchDetect', and 'trapDisplacement' from the 6th byte
    // 'doorStatus' is the least significant bit (bit 0)
    // 'catchDetect' is the second least significant bit (bit 1)
    // 'trapDisplacement' is the third least significant bit (bit 2)
    data.doorStatus = (bytes[5] & 1) !== 0;          // Extracts bit 0
    data.catchDetect = (bytes[5] & 2) !== 0;         // Extracts bit 1
    data.trapDisplacement = (bytes[5] & 4) !== 0;    // Extracts bit 2
    
    // Decode 'batteryStatus' from the 7th byte
    // The 'batteryStatus' is a single byte indicating the battery status
    data.batteryStatus = bytes[6];
    
    // Decode 'unixTime' from bytes 7 to 10
    // The 'unixTime' is a 32-bit integer representing the timestamp
    data.unixTime = (bytes[7] << 24) | (bytes[8] << 16) | (bytes[9] << 8) | bytes[10];
    
    // Return the decoded data and the raw bytes
    return {
      data: {
        data: data,
        raw: input.bytes
      }
    };
  }
  