#ifndef KOKO_OPCODES_C
#define KOKO_OPCODES_C

/**
 * takes in a byte (char) of bytecode,
 * and returns a string representation of
 * the opcode
 */
char* char_to_opcode(unsigned char c) {
    char* result = "UNKOWN";
    switch (c) {
        case 00:
            result = "NOP";
            break;
        case 0x32:
            result = "aaload";
            break;
        case 0x53:
            result = "aastore";
            break;
        case 0x01:
            result = "aconst_null";
            break;
        case 0x19:
            result = "aload";
            break;
        case 0x2a:
            result = "aload_0";
            break;
        case 0x2b:
            result = "aload_1";
            break;
        case 0x2c:
            result = "aload_2";
            break;
        case 0x2d:
            result = "aload_3";
            break;
        case 0xbd:
            result = "anewarray";
            break;
        case 0xb0:
            result = "areturn";
            break;
        case 0xbe:
            result = "arraylength";
            break;
        case 0x3a:
            result = "astore";
            break;
        case 0x4b:
            result = "astore_0";
            break;
        case 0x4c:
            result = "astore_1";
            break;
        case 0x4d:
            result = "astore_2";
            break;
        case 0x4e:
            result = "astore_3";
            break;
        case 0xbf:
            result = "athrow";
            break;
        case 0x33:
            result = "baload";
            break;
        case 0x54:
            result = "bastore";
            break;
        case 0x10:
            result = "bipush";
            break;
        case 0xca:
            result = "breakpoint";
            break;
        case 0x34:
            result = "caload";
            break;
        case 0x55:
            result = "castore";
            break;
        case 0xc0:
            result = "checkcast";
            break;
        case 0x90:
            result = "d2f";
            break;
        case 0x8e:
            result = "d2i";
            break;
        case 0x8f:
            result = "d2l";
            break;
        case 0x63:
            result = "dadd";
            break;
        case 0x31:
            result = "daload";
            break;
        case 0x52:
            result = "dastore";
            break;
        case 0x98:
            result = "dcmpg";
            break;
        case 0x97:
            result = "dcmpl";
            break;
        case 0x0e:
            result = "dconst_0";
            break;
        case 0x0f:
            result = "dconst_1";
            break;
        case 0x6f:
            result = "ddiv";
            break;
        case 0x18:
            result = "dload";
            break;
        case 0x26:
            result = "dload_0";
            break;
        case 0x27:
            result = "dload_1";
            break;
        case 0x28:
            result = "dload_2";
            break;
        case 0x29:
            result = "dload_3";
            break;
        case 0x6b:
            result = "dmul";
            break;
        case 0x77:
            result = "dneg";
            break;
        case 0x73:
            result = "drem";
            break;
        case 0xaf:
            result = "dreturn";
            break;
        case 0x39:
            result = "dstore";
            break;
        case 0x47:
            result = "dstore_0";
            break;
        case 0x48:
            result = "dstore_1";
            break;
        case 0x49:
            result = "dstore_2";
            break;
        case 0x4a:
            result = "dstore_3";
            break;
        case 0x67:
            result = "dsub";
            break;
        case 0x59:
            result = "dup";
            break;
        case 0x5a:
            result = "dup_x1";
            break;
        case 0x5b:
            result = "dup_x2";
            break;
        case 0x5c:
            result = "dup2";
            break;
        case 0x5d:
            result = "dup2_x1";
            break;
        case 0x5e:
            result = "dup2_x2";
            break;
        case 0x8d:
            result = "f2d";
            break;
        case 0x8b:
            result = "f2i";
            break;
        case 0x8c:
            result = "f2l";
            break;
        case 0x62:
            result = "fadd";
            break;
        case 0x30:
            result = "faload";
            break;
        case 0x51:
            result = "fastore";
            break;
        case 0x96:
            result = "fcmpg";
            break;
        case 0x95:
            result = "fcmpl";
            break;
        case 0x0b:
            result = "fconst_0";
            break;
        case 0x0c:
            result = "fconst_1";
            break;
        case 0x0d:
            result = "fconst_2";
            break;
        case 0x6e:
            result = "fdiv";
            break;
        case 0x17:
            result = "fload";
            break;
        case 0x22:
            result = "fload_0";
            break;
        case 0x23:
            result = "fload_1";
            break;
        case 0x24:
            result = "fload_2";
            break;
        case 0x25:
            result = "fload_3";
            break;
        case 0x6a:
            result = "fmul";
            break;
        case 0x76:
            result = "fneg";
            break;
        case 0x72:
            result = "frem";
            break;
        case 0xae:
            result = "freturn";
            break;
        case 0x38:
            result = "fstore";
            break;
        case 0x43:
            result = "fstore_0";
            break;
        case 0x44:
            result = "fstore_1";
            break;
        case 0x45:
            result = "fstore_2";
            break;
        case 0x46:
            result = "fstore_3";
            break;
        case 0x66:
            result = "fsub";
            break;
        case 0xb4:
            result = "getfield";
            break;
        case 0xb2:
            result = "getstatic";
            break;
        case 0xa7:
            result = "goto";
            break;
        case 0xc8:
            result = "goto_w";
            break;
        case 0x91:
            result = "i2b";
            break;
        case 0x92:
            result = "i2c";
            break;
        case 0x87:
            result = "i2d";
            break;
        case 0x86:
            result = "i2f";
            break;
        case 0x85:
            result = "i2l";
            break;
        case 0x93:
            result = "i2s";
            break;
        case 0x60:
            result = "iadd";
            break;
        case 0x2e:
            result = "iaload";
            break;
        case 0x7e:
            result = "iand";
            break;
        case 0x4f:
            result = "iastore";
            break;
        case 0x02:
            result = "iconst_m1";
            break;
        case 0x03:
            result = "iconst_0";
            break;
        case 0x04:
            result = "iconst_1";
            break;
        case 0x05:
            result = "iconst_2";
            break;
        case 0x06:
            result = "iconst_3";
            break;
        case 0x07:
            result = "iconst_4";
            break;
        case 0x08:
            result = "iconst_5";
            break;
        case 0x6c:
            result = "idiv";
            break;
        case 0xa5:
            result = "if_acmpeq";
            break;
        case 0xa6:
            result = "if_acmpne";
            break;
        case 0x9f:
            result = "if_icmpeq";
            break;
        case 0xa2:
            result = "if_icmpge";
            break;
        case 0xa3:
            result = "if_icmpgt";
            break;
        case 0xa4:
            result = "if_icmple";
            break;
        case 0xa1:
            result = "if_icmplt";
            break;
        case 0xa0:
            result = "if_icmpne";
            break;
        case 0x99:
            result = "ifeq";
            break;
        case 0x9c:
            result = "ifge";
            break;
        case 0x9d:
            result = "ifgt";
            break;
        case 0x9e:
            result = "ifle";
            break;
        case 0x9b:
            result = "iflt";
            break;
        case 0x9a:
            result = "ifne";
            break;
        case 0xc7:
            result = "ifnonnull";
            break;
        case 0xc6:
            result = "ifnull";
            break;
        case 0x84:
            result = "iinc";
            break;
        case 0x15:
            result = "iload";
            break;
        case 0x1a:
            result = "iload_0";
            break;
        case 0x1b:
            result = "iload_1";
            break;
        case 0x1c:
            result = "iload_2";
            break;
        case 0x1d:
            result = "iload_3";
            break;
        case 0xfe:
            result = "impdep1";
            break;
        case 0xff:
            result = "impdep2";
            break;
        case 0x68:
            result = "imul";
            break;
        case 0x74:
            result = "ineg";
            break;
        case 0xc1:
            result = "instanceof";
            break;
        case 0xba:
            result = "invokedynamic";
            break;
        case 0xb9:
            result = "invokeinterface";
            break;
        case 0xb7:
            result = "invokespecial";
            break;
        case 0xb8:
            result = "invokestatic";
            break;
        case 0xb6:
            result = "invokevirtual";
            break;
        case 0x80:
            result = "ior";
            break;
        case 0x70:
            result = "irem";
            break;
        case 0xac:
            result = "ireturn";
            break;
        case 0x78:
            result = "ishl";
            break;
        case 0x7a:
            result = "ishr";
            break;
        case 0x36:
            result = "istore";
            break;
        case 0x3b:
            result = "istore_0";
            break;
        case 0x3c:
            result = "istore_1";
            break;
        case 0x3d:
            result = "istore_2";
            break;
        case 0x3e:
            result = "istore_3";
            break;
        case 0x64:
            result = "isub";
            break;
        case 0x7c:
            result = "iushr";
            break;
        case 0x82:
            result = "ixor";
            break;
        case 0xa8:
            result = "jsr";
            break;
        case 0xc9:
            result = "jsr_w";
            break;
        case 0x8a:
            result = "l2d";
            break;
        case 0x89:
            result = "l2f";
            break;
        case 0x88:
            result = "l2i";
            break;
        case 0x61:
            result = "ladd";
            break;
        case 0x2f:
            result = "laload";
            break;
        case 0x7f:
            result = "land";
            break;
        case 0x50:
            result = "lastore";
            break;
        case 0x94:
            result = "lcmp";
            break;
        case 0x09:
            result = "lconst_0";
            break;
        case 0x0a:
            result = "lconst_1";
            break;
        case 0x12:
            result = "ldc";
            break;
        case 0x13:
            result = "ldc_w";
            break;
        case 0x14:
            result = "ldc2_w";
            break;
        case 0x6d:
            result = "ldiv";
            break;
        case 0x16:
            result = "lload";
            break;
        case 0x1e:
            result = "lload_0";
            break;
        case 0x1f:
            result = "lload_1";
            break;
        case 0x20:
            result = "lload_2";
            break;
        case 0x21:
            result = "lload_3";
            break;
        case 0x69:
            result = "lmul";
            break;
        case 0x75:
            result = "lneg";
            break;
        case 0xab:
            result = "lookupswitch";
            break;
        case 0x81:
            result = "lor";
            break;
        case 0x71:
            result = "lrem";
            break;
        case 0xad:
            result = "lreturn";
            break;
        case 0x79:
            result = "lshl";
            break;
        case 0x7b:
            result = "lshr";
            break;
        case 0x37:
            result = "lstore";
            break;
        case 0x3f:
            result = "lstore_0";
            break;
        case 0x40:
            result = "lstore_1";
            break;
        case 0x41:
            result = "lstore_2";
            break;
        case 0x42:
            result = "lstore_3";
            break;
        case 0x65:
            result = "lsub";
            break;
        case 0x7d:
            result = "lushr";
            break;
        case 0x83:
            result = "lxor";
            break;
        case 0xc2:
            result = "monitorenter";
            break;
        case 0xc3:
            result = "monitorexit";
            break;
        case 0xc5:
            result = "multianewarray";
            break;
        case 0xbb:
            result = "new";
            break;
        case 0xbc:
            result = "newarray";
            break;
        case 0x57:
            result = "pop";
            break;
        case 0x58:
            result = "pop2";
            break;
        case 0xb5:
            result = "putfield";
            break;
        case 0xb3:
            result = "putstatic";
            break;
        case 0xa9:
            result = "ret";
            break;
        case 0xb1:
            result = "return";
            break;
        case 0x35:
            result = "saload";
            break;
        case 0x56:
            result = "sastore";
            break;
        case 0x11:
            result = "sipush";
            break;
        case 0x5f:
            result = "swap";
            break;
    }
    return result;
}

#endif
