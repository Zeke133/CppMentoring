#ifndef ZIPPER_TYPES_H
#define ZIPPER_TYPES_H

using std::string;

enum class VERSION_MADE_BY : uint8_t
{
    MS_DOS,                             // 0 - MS-DOS and OS/2 (FAT / VFAT / FAT32 file systems)
    Amiga,                              // 1 - Amiga
    OpenVMS,                            // 2 - OpenVMS
    UNIX,                               // 3 - UNIX
    VM_CMS,                             // 4 - VM/CMS
    Atari,                              // 5 - Atari ST
    OS_2,                               // 6 - OS/2 H.P.F.S.
    Macintosh,                          // 7 - Macintosh
    Z_System,                           // 8 - Z-System
    CP_M,                               // 9 - CP/M
    NTFS,                               // 10 - Windows NTFS
    MVS,                                // 11 - MVS (OS/390 - Z/OS)
    VSE,                                // 12 - VSE
    Acorn_Risc,                         // 13 - Acorn Risc
    VFAT,                               // 14 - VFAT
    alternate_MVS,                      // 15 - alternate MVS
    BeOS,                               // 16 - BeOS
    Tandem,                             // 17 - Tandem
    OS_400,                             // 18 - OS/400
    OS_X,                               // 19 - OS/X (Darwin)
                                        // 20 - 255: unused
};

struct VERSION
{
    uint8_t zip_spec;                   //lower byte: zip specification version
    VERSION_MADE_BY made_by;            //upper byte: Version made by
};

// General purpose bit flag:
struct FLAGS
{
    uint16_t encrypted_file:1;          // Bit 00: encrypted file
    uint16_t compression_opt1:1;        // Bit 01: compression option
    uint16_t compression_opt2:1;        // Bit 02: compression option
    uint16_t data_descriptor:1;         // Bit 03: data descriptor
    uint16_t enhanced_deflation:1;      // Bit 04: enhanced deflation
    uint16_t comp_patched_data:1;       // Bit 05: compressed patched data
    uint16_t strong_encryption:1;       // Bit 06: strong encryption
    uint16_t :4;                        // Bit 07-10: unused
    uint16_t language_encoding:1;       // Bit 11: language encoding
    uint16_t reserved:1;                // Bit 12: reserved
    uint16_t mask_header_values:1;      // Bit 13: mask header values
    uint16_t :0;                        // Bit 14-15: reserved
};

// Compression method
enum class COMPRESSION : uint16_t
{
    no,                                 // 00: no compression
    shrunk,                             // 01: shrunk
    reduced_1,                          // 02: reduced with compression factor 1
    reduced_2,                          // 03: reduced with compression factor 2
    reduced_3,                          // 04: reduced with compression factor 3
    reduced_4,                          // 05: reduced with compression factor 4
    imploded,                           // 06: imploded
                                        // 07: reserved
    deflated = 8,                       // 08: deflated
    enh_deflated,                       // 09: enhanced deflated
    PKWare,                             // 10: PKWare DCL imploded
                                        // 11: reserved
    BZIP2 = 12,                         // 12: compressed using BZIP2
                                        // 13: reserved
    LZMA = 14,                          // 14: LZMA
                                        // 15-17: reserved
    IBM_TERSE = 18,                     // 18: compressed using IBM TERSE
    IBM_LZ77,                           // 19: IBM LZ77 z
    PPMd = 98                           // 98: PPMd version I, Rev 1
};

struct MS_DOS_TIME
{
    uint16_t seconds_div_by_2:5;        //Bits 00-04: seconds divided by 2
    uint16_t minute:6;                  //Bits 05-10: minute
    uint16_t hour:5;                    //Bits 11-15: hour
};

struct MS_DOS_DATE
{
    uint16_t day:5;                     //Bits 00-04: day
    uint16_t month:4;                   //Bits 05-08: month
    uint16_t years_from_1980:7;         //Bits 09-15: years from 1980
};

// Internal file attributes:
struct INT_ATTR
{
    uint16_t ASCII_text:1;              // Bit 0: apparent ASCII/text file
    uint16_t reserved:1;                // Bit 1: reserved
    uint16_t control:1;                 // Bit 2: control field records precede logical records
    uint16_t :0;                        // Bits 3-16: unused
};

//---------------------------------------------------
//------------------STRUCTURES-----------------------
//---------------------------------------------------

// End of central directory record
#define ZIP_END_OF_CD_SIGNATURE         0x06054b50
#pragma pack(push,1)
struct ZIP_END_OF_CD    {
    uint32_t  signature;                // The signature of end of central directory record. This is always '\x50\x4b\x05\x06'.
    uint16_t  disk_num;                 // The number of this disk (containing the end of central directory record)
    uint16_t  disk_num_wcd;             // Number of the disk on which the central directory starts
    uint16_t  disk_entries;             // The number of central directory entries on this disk
    uint16_t  total_entries;            // Total number of entries in the central directory.
    uint32_t  cd_size;                  // Size of the central directory in bytes
    uint32_t  offset;                   // Offset of the start of the central directory on the disk on which the central directory starts
    uint16_t  comment_len;              // The length of the following comment field
    //uint8_t   comment[];              // Optional comment for the Zip file
    uint32_t    getRealSize() const
    {
        return sizeof(ZIP_END_OF_CD) + this->comment_len;
    }
    string GetComment() const
    {
        return string((const char *)(this+1), this->comment_len);
    }
};
#pragma pack(pop)

// Central directory file header
#define ZIP_CD_FILE_HEADER_SIGNATURE    0x02014b50
#pragma pack(push,1)
struct ZIP_CD_FILE_HEADER    {
    uint32_t    signature;              // The signature of the file header. This is always '\x50\x4b\x01\x02'.
    VERSION     version;                // Version:
    uint16_t    version_needed;         // PKZip version needed to extract
    FLAGS       flags;                  // General purpose bit flag:
    COMPRESSION compression;            // Compression method:
    MS_DOS_TIME mod_time;               // File modification time 	stored in standard MS-DOS format:
    MS_DOS_DATE mod_date;               // File modification date 	stored in standard MS-DOS format:
    uint32_t    crc32;                  // Crc-32 checksum 	value computed over file data by CRC-32 algorithm with 'magic number' 0xdebb20e3 (little endian)
    uint32_t    compressed_size;        // Compressed size 	if archive is in ZIP64 format, this filed is 0xffffffff and the length is stored in the extra field
    uint32_t    uncompressed_size;      // Uncompressed size 	if archive is in ZIP64 format, this filed is 0xffffffff and the length is stored in the extra field
    uint16_t    file_name_len;          // File name length 	the length of the file name field below
    uint16_t    extra_field_len;        // Extra field length 	the length of the extra field below
    uint16_t    file_comm_len;          // File comm. len 	the length of the file comment
    uint16_t    disk_start;             // Disk # start 	the number of the disk on which this file exists
    INT_ATTR    internal_attr;          // Internal file attributes:
    uint32_t    external_attr;          // External file attributes: host-system dependent
    uint32_t    offset_local_header;    // Relative offset of local header. This is the offset of where to find the corresponding local file header from the start of the first disk.
    // uint8_t     file_name[];         // the name of the file including an optional relative path. All slashes in the path should be forward slashes '/'.
    // uint8_t     extra_field[];       // Used to store additional information. The field consistes of a sequence of header and data pairs, where the header has a 2 byte identifier and a 2 byte data size field.
    // uint8_t     file_comment[];      // An optional comment for the file.
    string GetName() const
    {
        return string((const char *)(this+1), this->file_name_len);
    }
    string GetExtraField() const
    {
        return string((const char *)(this+1) + this->file_name_len, this->extra_field_len);
    }
    string GetComment() const
    {
        return string((const char *)(this+1) + this->file_name_len + this->extra_field_len, this->file_comm_len);
    }
    uint32_t    getRealSize() const
    {
        return sizeof(ZIP_CD_FILE_HEADER) + this->file_name_len + this->extra_field_len + this->file_comm_len;
    }
};
#pragma pack(pop)

// Local file headers
#define ZIP_LOCAL_FILE_HEADER_SIGNATURE 0x04034b50
#pragma pack(push,1)
struct ZIP_LOCAL_FILE_HEADER    {
    uint32_t    signature;              // The signature of the file header. This is always '\x50\x4b\x03\x04'.
    uint16_t    version_needed;         // PKZip version needed to extract
    FLAGS       flags;                  // General purpose bit flag:
    COMPRESSION compression;            // Compression method:
    MS_DOS_TIME mod_time;               // File modification time 	stored in standard MS-DOS format:
    MS_DOS_DATE mod_date;               // File modification date 	stored in standard MS-DOS format:
    uint32_t    crc32;                  // Crc-32 checksum 	value computed over file data by CRC-32 algorithm with 'magic number' 0xdebb20e3 (little endian)
    uint32_t    compressed_size;        // Compressed size 	if archive is in ZIP64 format, this filed is 0xffffffff and the length is stored in the extra field
    uint32_t    uncompressed_size;      // Uncompressed size 	if archive is in ZIP64 format, this filed is 0xffffffff and the length is stored in the extra field
    uint16_t    file_name_len;          // File name length 	the length of the file name field below
    uint16_t    extra_field_len;        // Extra field length 	the length of the extra field below
    // uint8_t     file_name[];            // the name of the file including an optional relative path. All slashes in the path should be forward slashes '/'.
    // uint8_t     extra_field[];          // Used to store additional information. The field consistes of a sequence of header and data pairs, where the header has a 2 byte identifier and a 2 byte data size field.
    string GetName() const
    {
        return string((const char *)(this+1), this->file_name_len);
    }
    string GetExtraField() const
    {
        return string((const char *)(this+1) + this->file_name_len, this->extra_field_len);
    }
    uint32_t    getRealSize() const
    {
        return sizeof(ZIP_LOCAL_FILE_HEADER) + this->file_name_len + this->extra_field_len;
    }
};
#pragma pack(pop)

// sizeof(VERSION) = 2
// sizeof(VERSION_MADE_BY) = 1
// sizeof(FLAGS) = 2
// sizeof(COMPRESSION) = 2
// sizeof(MS_DOS_TIME) = 2
// sizeof(MS_DOS_DATE) = 2
// sizeof(INT_ATTR) = 2
// sizeof(ZIP_END_OF_CD) = 24
// sizeof(ZIP_CD_FILE_HEADER) = 46
// sizeof(ZIP_LOCAL_FILE_HEADER) = 30

#endif

