#include "Zipper.h"

using namespace std;

ostream &operator<<( ostream &output, const VERSION_MADE_BY &ver)
{
    switch (ver)
    {
        case MS_DOS:    output << "MS_DOS";     break;
        case Amiga:     output << "Amiga";      break;
        case OpenVMS:   output << "OpenVMS";    break;
        case UNIX:      output << "UNIX";       break;
        case VM_CMS:    output << "VM_CMS";     break;
        case Atari:     output << "Atari";      break;
        case OS_2:      output << "OS_2";       break;
        case Macintosh: output << "Macintosh";  break;
        case Z_System:  output << "Z_System";   break;
        case CP_M:      output << "CP_M";       break;
        case NTFS:      output << "NTFS";       break;
        case MVS:       output << "MVS";        break;
        case VSE:       output << "VSE";        break;
        case Acorn_Risc: output << "Acorn_Risc"; break;
        case VFAT:      output << "VFAT";       break;
        case alternate_MVS: output << "alternate_MVS"; break;
        case BeOS:      output << "BeOS";       break;
        case Tandem:    output << "Tandem";     break;
        case OS_400:    output << "OS_400";     break;
        case OS_X:      output << "OS_X";       break;
        default:        output << "UNKNOWN!";   break;
    }

    return output;
}

ostream &operator<<( ostream &output, const VERSION &ver)
{
    output << "zip specification version = " << (uint32_t)ver.zip_spec << " made by = " << ver.made_by << " - " << (uint32_t)ver.made_by;

    return output;
}

void put_n(ostream &output, const uint8_t * str, uint32_t len)
{    
    const uint8_t * end = str + len;

    while(str < end)
        output.put(*str++);
}

ostream &operator<<( ostream &output, const ZIP_LOCAL_FILE_HEADER &locFileHeader)
{
    output << "Local file header:" << endl;

    output <<  hex << showbase;

    output << "\t" << "signature: " << locFileHeader.signature << endl;
    output << "\t" << "version: " << locFileHeader.version << endl;
    //output << "\t" << "flags: " << locFileHeader.flags << endl;
    output << "\t" << "compression: " << locFileHeader.compression << endl;
    // output << "\t" << "mod_time: " << locFileHeader.mod_time << endl;
    // output << "\t" << "mod_date: " << locFileHeader.mod_date << endl;
    output << "\t" << "crc32: " << locFileHeader.crc32 << endl;

    output <<  dec;

    output << "\t" << "compressed_size: " << locFileHeader.compressed_size << endl;
    output << "\t" << "uncompressed_size: " << locFileHeader.uncompressed_size << endl;
    output << "\t" << "file_name_len: " << locFileHeader.file_name_len << endl;
    output << "\t" << "extra_field_len: " << locFileHeader.extra_field_len << endl;
    
    uint8_t * str = (uint8_t*)&((&locFileHeader)[1]);
    if(locFileHeader.file_name_len)
    {
        output << "\t" << "file_name: ";
        put_n(output, str, locFileHeader.file_name_len);
        output << endl;
        str += locFileHeader.file_name_len;
    }
    if(locFileHeader.extra_field_len)
    {
        output << "\t" << "extra_field: ";
        put_n(output, str, locFileHeader.extra_field_len);
        output << endl;
    }

    return output;
}

ostream &operator<<( ostream &output, const ZIP_CD_FILE_HEADER &cdFileHeader)
{
    output << "Central Directory file header:" << endl;

    output <<  hex << showbase;

    output << "\t" << "signature: " << cdFileHeader.signature << endl;
    //output << "\t" << "version: " << cdFileHeader.version << endl;
    output << "\t" << "version_needed: " << cdFileHeader.version_needed << endl;
    //output << "\t" << "flags: " << cdFileHeader.flags << endl;
    output << "\t" << "compression: " << cdFileHeader.compression << endl;
    // output << "\t" << "mod_time: " << cdFileHeader.mod_time << endl;
    // output << "\t" << "mod_date: " << cdFileHeader.mod_date << endl;
    output << "\t" << "crc32: " << cdFileHeader.crc32 << endl;

    output <<  dec;

    output << "\t" << "compressed_size: " << cdFileHeader.compressed_size << endl;
    output << "\t" << "uncompressed_size: " << cdFileHeader.uncompressed_size << endl;
    output << "\t" << "file_name_len: " << cdFileHeader.file_name_len << endl;
    output << "\t" << "extra_field_len: " << cdFileHeader.extra_field_len << endl;
    output << "\t" << "file_comm_len: " << cdFileHeader.file_comm_len << endl;
    output << "\t" << "disk_start: " << cdFileHeader.disk_start << endl;

    output <<  hex << showbase;

    // output << "\t" << "internal_attr: " << cdFileHeader.internal_attr << endl;
    output << "\t" << "external_attr: " << cdFileHeader.external_attr << endl;
    output << "\t" << "offset_local_header: " << cdFileHeader.offset_local_header << " = " << dec << cdFileHeader.offset_local_header << endl;
    
    uint8_t * str = (uint8_t*)&((&cdFileHeader)[1]);
    if(cdFileHeader.file_name_len)
    {
        output << "\t" << "file_name: ";
        put_n(output, str, cdFileHeader.file_name_len);
        output << endl;
        str += cdFileHeader.file_name_len;
    }
    if(cdFileHeader.extra_field_len)
    {
        output << "\t" << "extra_field: ";
        put_n(output, str, cdFileHeader.extra_field_len);
        output << endl;
        str += cdFileHeader.extra_field_len;
    }
    if(cdFileHeader.file_comm_len)
    {
        output << "\t" << "file_comment: ";
        put_n(output, str, cdFileHeader.file_comm_len);
        output << endl;
    }
    
    return output;
}

ostream &operator<<( ostream &output, const ZIP_END_OF_CD &endOfCd)
{
    output << "End of Central Directory:" << endl;

    output <<  hex << showbase;

    output << "\t" << "signature: " << endOfCd.signature << endl;

    output <<  dec;

    output << "\t" << "disk_num: " << endOfCd.disk_num << endl;
    output << "\t" << "disk_num_wcd: " << endOfCd.disk_num_wcd << endl;
    output << "\t" << "disk_entries: " << endOfCd.disk_entries << endl;
    output << "\t" << "total_entries: " << endOfCd.total_entries << endl;
    output << "\t" << "cd_size: " << endOfCd.cd_size <<  " bytes" << endl;

    output <<  hex << showbase;

    output << "\t" << "offset: " << endOfCd.offset << " = " << dec << endOfCd.offset << endl;
    output << "\t" << "comment_len: " << endOfCd.comment_len << endl;

    uint8_t * str = (uint8_t*)&((&endOfCd)[1]);
    if(endOfCd.comment_len)
    {
        output << "\t" << "comment_len: ";
        put_n(output, str, endOfCd.comment_len);
        output << endl;
    }

    return output;
}

Zipper::Zipper(int8_t * file, int32_t size)
{
    cout << "Zipper get file" << endl;

    ZIP_END_OF_CD * endOfCd = GetZipEndOfCentralDirectory(file, size);
    
    if(endOfCd == nullptr)
    {
        cerr << "Error in ZIP file endOfCentralDirectory record!";
        return;
    }
    else
    {
        cout << *endOfCd;
    }

    ZIP_CD_FILE_HEADER * cdFileHeader = (ZIP_CD_FILE_HEADER *)(file + endOfCd->offset);
    cout << *cdFileHeader;

    ZIP_LOCAL_FILE_HEADER * localFileHeader = (ZIP_LOCAL_FILE_HEADER *)(file + cdFileHeader->offset_local_header);
    cout << *localFileHeader;

}

Zipper::~Zipper()
{
    cout << "Destructor" << endl;
}

// Return nullptr if error
ZIP_END_OF_CD * Zipper::GetZipEndOfCentralDirectory(int8_t * file, int32_t size)
{
    int8_t * ptr = file;

    ptr += size;
    while(ptr > file && !(*ptr == 0x50 && *(ptr+1) == 0x4b && *(ptr+2) == 0x05 && *(ptr+3) == 0x06))
    {
        ptr--;
    }
    
    return (ZIP_END_OF_CD *)(ptr > file ? ptr : nullptr);
}





