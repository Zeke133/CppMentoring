#include "ZipperOstreams.h"

ostream &operator<<( ostream &output, const VERSION_MADE_BY &ver)
{
    switch (ver)
    {
        case VERSION_MADE_BY::MS_DOS:    output << "MS_DOS";     break;
        case VERSION_MADE_BY::Amiga:     output << "Amiga";      break;
        case VERSION_MADE_BY::OpenVMS:   output << "OpenVMS";    break;
        case VERSION_MADE_BY::UNIX:      output << "UNIX";       break;
        case VERSION_MADE_BY::VM_CMS:    output << "VM_CMS";     break;
        case VERSION_MADE_BY::Atari:     output << "Atari";      break;
        case VERSION_MADE_BY::OS_2:      output << "OS_2";       break;
        case VERSION_MADE_BY::Macintosh: output << "Macintosh";  break;
        case VERSION_MADE_BY::Z_System:  output << "Z_System";   break;
        case VERSION_MADE_BY::CP_M:      output << "CP_M";       break;
        case VERSION_MADE_BY::NTFS:      output << "NTFS";       break;
        case VERSION_MADE_BY::MVS:       output << "MVS";        break;
        case VERSION_MADE_BY::VSE:       output << "VSE";        break;
        case VERSION_MADE_BY::Acorn_Risc: output << "Acorn_Risc"; break;
        case VERSION_MADE_BY::VFAT:      output << "VFAT";       break;
        case VERSION_MADE_BY::alternate_MVS: output << "alternate_MVS"; break;
        case VERSION_MADE_BY::BeOS:      output << "BeOS";       break;
        case VERSION_MADE_BY::Tandem:    output << "Tandem";     break;
        case VERSION_MADE_BY::OS_400:    output << "OS_400";     break;
        case VERSION_MADE_BY::OS_X:      output << "OS_X";       break;
        default:                         output << "UNKNOWN!";   break;
    }
    return output;
}

ostream &operator<<( ostream &output, const COMPRESSION &compression)
{
    switch (compression)
    {
        case COMPRESSION::no:            output << "no";                                         break;
        case COMPRESSION::shrunk:        output << "shrunk";                                     break;
        case COMPRESSION::reduced_1:     output << "reduced with compression factor 1";          break;
        case COMPRESSION::reduced_2:     output << "reduced with compression factor 2";          break;
        case COMPRESSION::reduced_3:     output << "reduced with compression factor 3";          break;
        case COMPRESSION::reduced_4:     output << "reduced with compression factor 4";          break;
        case COMPRESSION::imploded:      output << "imploded";                                   break;
        case COMPRESSION::deflated:      output << "deflated";                                   break;
        case COMPRESSION::enh_deflated:  output << "enhanced deflated";                          break;
        case COMPRESSION::PKWare:        output << "PKWare DCL imploded";                        break;
        case COMPRESSION::BZIP2:         output << "compressed using BZIP2";                     break;
        case COMPRESSION::LZMA:          output << "LZMA";                                       break;
        case COMPRESSION::IBM_TERSE:     output << "compressed using IBM TERSE";                 break;
        case COMPRESSION::IBM_LZ77:      output << "IBM LZ77 z";                                 break;
        case COMPRESSION::PPMd:          output << "PPMd version I, Rev 1";                      break;
        default:                         output << "UNKNOWN!";                                   break;
    }
    return output;
};

ostream &operator<<( ostream &output, const FLAGS &flags)
{
    const int bit_count = 16;
    const char * bit_names[bit_count] = 
    {
        "encrypted file",
        "compression option_1",
        "compression option_2",
        "data descriptor",
        "enhanced deflation",
        "compressed patched data",
        "strong encryption",
        "unused_1",
        "unused_2",
        "unused_3",
        "unused_4",
        "language encoding",
        "reserved",
        "mask header values",
        "reserved_1",
        "reserved_2"
    };

    static_assert(bit_count == (sizeof(FLAGS)*8));

    const uint16_t bits = *((const uint16_t *)&flags);
    bool past = false;

    for (int i = 0; i < bit_count; i++)
    {
        if( (bits >> i) & 1 )
        {
            if(past)    output << " | ";
            output << bit_names[i];
            past = true;
        }
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
    
    output << "\t" << "file_name: " << locFileHeader.GetName() << endl;
    output << "\t" << "extra_field: " << locFileHeader.GetExtraField() << endl;
    
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
    
    output << "\t" << "file_name: " << cdFileHeader.GetName() << endl;
    output << "\t" << "extra_field: " << cdFileHeader.GetExtraField() << endl;
    output << "\t" << "extra_field: " << cdFileHeader.GetComment() << endl;
        
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

    output << "\t" << "extra_field: " << endOfCd.GetComment() << endl;

    return output;
}


