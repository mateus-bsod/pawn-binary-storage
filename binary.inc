//          88""Yb 88 88b 88    db    88""Yb Yb  dP 
//          88__dP 88 88Yb88   dPYb   88__dP  YbdP  
//          88""Yb 88 88 Y88  dP__Yb  88"Yb    8P   
//          88oodP 88 88  Y8 dP""""Yb 88  Yb  dP    
//                  github.com/mateus-bsod

#if !defined _BIN_INCLUDED
    #define _BIN_INCLUDED
    #define BIN:: BIN_
#endif

#if !defined _BIN_ARRAY_INCLUDED
    #define _BIN_ARRAY_INCLUDED
#endif

// DEFINES

#if !defined _BIN_INVALID_
    #define _BIN_INVALID_ "(null)"
#endif

#if !defined MAX_BINARY_SIZE
    #define MAX_BINARY_SIZE 4096
#endif

#if !defined _BIN_LOGS
    #define _BIN_LOGS (false)
#endif

#if !defined isnull
    #define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#define fwritechar(%0)  fputchar(%0, false)
#define freadchar(%0)   fgetchar(%0, 0, false)

static _b_string[MAX_BINARY_SIZE];

//
// BINARY FILE
//

#define _B_PRINT1 "[binary.inc : \"%s\"] It is recommended that you use .bin extensions."
#define _B_PRINT2 "[binary.inc] I opened the \"%s\" file."
#define _B_PRINT3 "[binary.inc] I close the \"%s\" file."
#define _B_PRINT4 "[binary.inc] ReplaceKeyValue -> \"%s\"=%s"
#define _B_PRINT5 "[binary.inc] AddKeyValue -> \"%s\"=%s"
#define _B_PRINT6 "[binary.inc : %s=%s] You are trying to insert text into a non-existent file."
#define _B_PRINT7 "[binary.inc] You are trying to insert text into a non-existent file."

new File:_b_file, _b_filename[32];

BIN::Open(const file[])
{
    _b_filename[0] = '\0';
    strcat(_b_filename, file, 32);
    
    _b_file = fopen(file, io_read);
    
    if(_b_file)
    {
        _b_string[0] = '\0';
        fread(_b_file, _b_string, sizeof(_b_string));
        fclose(_b_file);
        
        _b_file = fopen(file, io_readwrite);
    }
    else
    {
        _b_file = fopen(file, io_write);
        if(!_b_file) return false;
        
        fclose(_b_file);
        _b_file = fopen(file, io_readwrite);
        _b_string[0] = '\0';
    }

    #if _BIN_LOGS
        printf(_B_PRINT2, file);
    #endif

    return true;
}

BIN::Save()
{
    if(!_b_file) return 0;
    
    new File:f = fopen(_b_filename, io_write);
    if(f)
    {
        fwrite(f, _b_string);
        fclose(f);
    }
    
    #if _BIN_LOGS
        printf(_B_PRINT3, _b_filename);
    #endif

    _b_filename[0] = '\0';
    fclose(_b_file);
    _b_file = File:0;
    
    return 1;
}

BIN::WriteFloat(key[], Float:value)
{
    new buf[32];
    format(buf, sizeof(buf), "%.8f", value);
    return BIN::WriteString(key, buf);
}

BIN::WriteInt(key[], value)
{
    new buf[16];
    format(buf, sizeof(buf), "%d", value);
    return BIN::WriteString(key, buf);
}

BIN::WriteString(key[], value[])
{
    if(_b_file)
    {
        if(BIN::BinKeyExists(key))
        {
            BIN::ReplaceKeyValue(key, value);
            #if _BIN_LOGS
                printf(_B_PRINT4, key, value);
            #endif
        }
        else
        {
            BIN::AddKeyValue(key, value);
            #if _BIN_LOGS
                printf(_B_PRINT5, key, value);
            #endif
        }
        
        return 1;
    }
    
    #if _BIN_LOGS
        printf(_B_PRINT6, key, value);
    #endif
    
    return 0;
}

BIN::BinKeyExists(const key[])
{
    new key_bin[256], format_str[64];
    format(format_str, sizeof(format_str), "[%s]=[", key);
    BIN::ConvertStr(format_str, key_bin, sizeof(key_bin));
    
    return (strfind(_b_string, key_bin) != -1);
}

BIN::GetKeyValue(key[])
{
    new value[(MAX_BINARY_SIZE/8)];
    BIN::GetKeyValueEx(key, value);
    return value;
}

BIN::GetKeyValueEx(const k[], v[], m = sizeof(v))
{
    v[0] = '\0';
    if(!_b_file) return 0;
    
    new s[(MAX_BINARY_SIZE/8)+1];
    BIN::BinStr(_b_string, s, sizeof(s));
    
    new p[64];
    format(p, 64, "[%s]=[", k);
    
    new st = strfind(s, p);
    if(st == -1) return 0;
    
    st += strlen(p);
    
    new e = strfind(s, "]", true, st);
    if(e == -1) return 0;
    
    strmid(v, s, st, e, m);
    return 1;
}

BIN::AddKeyValue(const key[], const value[])
{
    if(!_b_file)
    {
        #if _BIN_LOGS
            printf(_B_PRINT6, key, value);
        #endif
        return 0;
    }
    
    new string[128], binario[MAX_BINARY_SIZE];
    format(string, sizeof(string), "[%s]=[%s]", key, value);
    BIN::ConvertStr(string, binario, sizeof(binario));
    
    new len = strlen(_b_string);
    if(len > 0 && len < sizeof(_b_string) - 1)
    {
        _b_string[len] = ' ';
        _b_string[len + 1] = '\0';
    }
    
    strcat(_b_string, binario, sizeof(_b_string));
    return 1;
}

BIN::AppendRaw(const buffer[], size)
{
    if(!_b_file) return 0;
    
    strcat(_b_string, buffer, sizeof(_b_string));
    return strlen(buffer);
}

BIN::ReplaceKeyValue(key[], value[])
{
    if(!_b_file) return 0;
    
    new key_bin[256], fmt[64];
    format(fmt, sizeof(fmt), "[%s]=[", key);
    BIN::ConvertStr(fmt, key_bin, sizeof(key_bin));
    
    new pos = strfind(_b_string, key_bin);
    if(pos == -1) return 0;
    
    pos += strlen(key_bin);
    
    new end = pos;
    new temp[9];
    while(_b_string[end])
    {
        strmid(temp, _b_string, end, end + 8, sizeof(temp));
        if(temp[0] == '0' && temp[1] == '1' && temp[2] == '0' && temp[3] == '1' &&
           temp[4] == '1' && temp[5] == '1' && temp[6] == '0' && temp[7] == '1')
            break;
        end += 8;
    }
    
    if(!_b_string[end]) return 0;
    
    new val_bin[MAX_BINARY_SIZE];
    BIN::ConvertStr(value, val_bin, sizeof(val_bin));
    
    strdel(_b_string, pos, end);
    strins(_b_string, val_bin, pos, sizeof(_b_string));
    
    return 1;
}

BIN::WriteFile(const string[], filemode:mode = io_write)
{
    if(!_b_file) return 0;
    
    new File:f = fopen(_b_filename, mode);
    if(!f) return 0;
    
    if(mode == io_append)
    {
        BIN::AppendRaw(string, sizeof(string));
    }
    else
    {
        fwrite(f, string);
    }
    
    fclose(f);
    return 1;
}

//
// PARSER
//

BIN::ParserBIN(binary[], key[], value[])
{
    new str[(MAX_BINARY_SIZE/8)];
    BIN::BinStr(binary, str, sizeof(str));
    return BIN::Parser(str, key, value);
}

BIN::Parser(text[], key[], value[])
{
    new i = -1, stat = 0, pos = 0;
    
    while(text[++i])
    {
        switch(text[i])
        {
            case '[':
            {
                stat++;
                pos = 0;
            }
            case ']':
            {
                stat++;
                pos = 0;
            }
            default:
            {
                if(stat == 0) key[pos++] = text[i];
                else if(stat == 2) value[pos++] = text[i];
            }
        }
    }
    
    key[pos] = '\0';
    value[pos] = '\0';

    if(isnull(key)) format(key, 16, "_binary_invalid_");
    if(isnull(value)) format(value, 16, "_binary_invalid_");

    return 0;
}

//
// BINARY FUNCTIONS
//

BIN::IsBinary(const str[])
{
    new len = strlen(str);
    if(!len) return 0;
    
    new has_bits = 0;
    
    for(new i = 0; i < len; i++)
    {
        new ch = str[i];
        
        if(ch == '0' || ch == '1')
            has_bits = 1;
        else if(ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r')
            return 0;
    }
    
    return has_bits;
}

BIN::GetCharCountFromBin(const bin[])
{
    new byte_count = 0;
    new in_byte = false;
    
    for(new i = 0; bin[i]; i++)
    {
        new ch = bin[i];
        
        if(ch == '0' || ch == '1')
        {
            if(!in_byte)
            {
                byte_count++;
                in_byte = true;
            }
        }
        else
        {
            in_byte = false;
        }
    }
    
    return byte_count;
}

//
// STRING TO BINARY
//
BIN::ConvertStr(s[], o[], m = sizeof(o))
{
    new l = strlen(s);
    new p = 0;
    
    new limit = m - 8;
    
    for(new i = 0; i < l && p < limit; i++)
    {
        new c = s[i];
        
        o[p++] = (c & 0b10000000) ? '1' : '0';
        o[p++] = (c & 0b01000000) ? '1' : '0';
        o[p++] = (c & 0b00100000) ? '1' : '0';
        o[p++] = (c & 0b00010000) ? '1' : '0';
        o[p++] = (c & 0b00001000) ? '1' : '0';
        o[p++] = (c & 0b00000100) ? '1' : '0';
        o[p++] = (c & 0b00000010) ? '1' : '0';
        o[p++] = (c & 0b00000001) ? '1' : '0';
    }
    
    o[p] = '\0';
    return 1;
}

//
// BINARY TO STRING
//
BIN::BinStr(const b[], s[], max = sizeof(s))
{
    new bits[9], idx = 0, bit_idx = 0;
    new max_limit = max - 1;
    
    for(new i = 0; b[i] && idx < max_limit; i++)
    {
        new ch = b[i];
        
        if(ch == '0' || ch == '1')
        {
            bits[bit_idx++] = ch;
            
            if(bit_idx == 8)
            {
                bits[8] = '\0';
                
                new c = 0;
                if(bits[0] == '1') c |= 0b10000000;
                if(bits[1] == '1') c |= 0b01000000;
                if(bits[2] == '1') c |= 0b00100000;
                if(bits[3] == '1') c |= 0b00010000;
                if(bits[4] == '1') c |= 0b00001000;
                if(bits[5] == '1') c |= 0b00000100;
                if(bits[6] == '1') c |= 0b00000010;
                if(bits[7] == '1') c |= 0b00000001;
                
                s[idx++] = c;
                s[idx] = '\0';
                bit_idx = 0;
            }
        }
    }
    
    return 1;
}

#pragma dynamic 65536