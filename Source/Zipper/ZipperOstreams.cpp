#include "ZipperOstreams.h"

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

ostream &operator<<( ostream &output, const COMPRESSION &compression)
{
    switch (compression)
    {
        case no:            output << "no";                                         break;
        case shrunk:        output << "shrunk";                                     break;
        case reduced_1:     output << "reduced with compression factor 1";          break;
        case reduced_2:     output << "reduced with compression factor 2";          break;
        case reduced_3:     output << "reduced with compression factor 3";          break;
        case reduced_4:     output << "reduced with compression factor 4";          break;
        case imploded:      output << "imploded";                                   break;
        case deflated:      output << "deflated";                                   break;
        case enh_deflated:  output << "enhanced deflated";                          break;
        case PKWare:        output << "PKWare DCL imploded";                        break;
        case BZIP2:         output << "compressed using BZIP2";                     break;
        case LZMA:          output << "LZMA";                                       break;
        case IBM_TERSE:     output << "compressed using IBM TERSE";                 break;
        case IBM_LZ77:      output << "IBM LZ77 z";                                 break;
        case PPMd:          output << "PPMd version I, Rev 1";                      break;
        default:            output << "UNKNOWN!";                                   break;
    }
    return output;
};

ostream &operator<<( ostream &output, const FLAGS &flags)
{
    bool past = false;

    if(flags.encrypted_file)
    {
        output << "encrypted file";
        past = true;
    }
    if(flags.compression_opt1)
    {
        if(past)    output << " | ";
        output << "compression option 1";
        past = true;
    }
    if(flags.compression_opt2)
    {
        if(past)    output << " | ";
        output << "compression option 2";
        past = true;
    }
    if(flags.data_descriptor)
    {
        if(past)    output << " | ";
        output << "data descriptor";
        past = true;
    }
    if(flags.enhanced_deflation)
    {
        if(past)    output << " | ";
        output << "enhanced deflation";
        past = true;
    }
    if(flags.comp_patched_data)
    {
        if(past)    output << " | ";
        output << "compressed patched data";
        past = true;
    }
    if(flags.strong_encryption)
    {
        if(past)    output << " | ";
        output << "strong encryption";
        past = true;
    }
    if(flags.language_encoding)
    {
        if(past)    output << " | ";
        output << "language encoding";
        past = true;
    }
    if(flags.reserved)
    {
        if(past)    output << " | ";
        output << "reserved";
        past = true;
    }
    if(flags.mask_header_values)
    {
        if(past)    output << " | ";
        output << "mask header values";
        past = true;
    }
    
    return output;
};

ostream &operator<<( ostream &output, const INT_ATTR &attr)
{
    bool past = false;

    if(attr.ASCII_text)             output << "apparent ASCII/text file";
    if(past)    cout << " | ";
    if(attr.reserved)               output << "reserved";
    if(past)    cout << " | ";
    if(attr.control)                output << "control field records precede logical records";

    return output;
};

ostream &operator<<( ostream &output, const MS_DOS_TIME &time)
{
    output << dec << time.hour << ":" << time.minute << ":" << time.seconds_div_by_2*2;
    
    return output;
};

ostream &operator<<( ostream &output, const MS_DOS_DATE &date)
{
    output << dec << date.years_from_1980+1980 << "." << date.month << "." << date.day;
    
    return output;
};

ostream &operator<<( ostream &output, const VERSION &ver)
{
    output << *((uint16_t*)(&ver)) << " zip specification version - " << dec << (uint32_t)ver.zip_spec << " made by - " << ver.made_by;

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
    output << "Local file header:" << endl <<  hex << showbase;
    output << "\t" << "signature: " << locFileHeader.signature << endl;
    output << "\t" << "version needed: " << locFileHeader.version_needed << endl <<  hex << showbase;
    output << "\t" << "flags: " << locFileHeader.flags << endl;
    output << "\t" << "compression: " << locFileHeader.compression << endl;
    output << "\t" << "mod_time: " << locFileHeader.mod_time << endl;
    output << "\t" << "mod_date: " << locFileHeader.mod_date << endl << hex;
    output << "\t" << "crc32: " << locFileHeader.crc32 << endl <<  dec;
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
    output << "Central Directory file header:" << endl <<  hex << showbase;
    output << "\t" << "signature: " << cdFileHeader.signature << endl;
    output << "\t" << "version: " << cdFileHeader.version << endl <<  hex << showbase;
    output << "\t" << "version_needed: " << cdFileHeader.version_needed << endl;
    output << "\t" << "flags: " << cdFileHeader.flags << endl;
    output << "\t" << "compression: " << cdFileHeader.compression << endl;
    output << "\t" << "mod_time: " << cdFileHeader.mod_time << endl;
    output << "\t" << "mod_date: " << cdFileHeader.mod_date << endl << hex;
    output << "\t" << "crc32: " << cdFileHeader.crc32 << endl <<  dec;
    output << "\t" << "compressed_size: " << cdFileHeader.compressed_size << endl;
    output << "\t" << "uncompressed_size: " << cdFileHeader.uncompressed_size << endl;
    output << "\t" << "file_name_len: " << cdFileHeader.file_name_len << endl;
    output << "\t" << "extra_field_len: " << cdFileHeader.extra_field_len << endl;
    output << "\t" << "file_comm_len: " << cdFileHeader.file_comm_len << endl;
    output << "\t" << "disk_start: " << cdFileHeader.disk_start << endl <<  hex << showbase;
    output << "\t" << "internal_attr: " << cdFileHeader.internal_attr << endl;
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
    output << "End of Central Directory:" << endl <<  hex << showbase;
    output << "\t" << "signature: " << endOfCd.signature << endl <<  dec;
    output << "\t" << "disk_num: " << endOfCd.disk_num << endl;
    output << "\t" << "disk_num_wcd: " << endOfCd.disk_num_wcd << endl;
    output << "\t" << "disk_entries: " << endOfCd.disk_entries << endl;
    output << "\t" << "total_entries: " << endOfCd.total_entries << endl;
    output << "\t" << "cd_size: " << endOfCd.cd_size <<  " bytes" << endl <<  hex << showbase;
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


