#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "classFileStruct.h"
#include "instrucoes.h"

const int contagem_enum = jsr_w-nop;

instrucao* construirInstrucoes(void){

	instrucao *instrucoes = malloc(contagem_enum*sizeof(instrucao));

	for (int i = 0;i<contagem_enum;i++){
		switch(i){
			case nop:
				strcpy(instrucoes[i].inst_nome,"nop");
				instrucoes[i].opcode = nop;
				instrucoes[i].numarg = 0;
			break;
			case aconst_null:
				strpy(instrucoes[i].inst_nome,"aconst_null");
				instrucoes[i].opcode = aconst_null;
				instrucoes[i].numarg = 0;
			break;
			case iconst_m1:
			break;
			case iconst_0:
			break;
			case iconst_1:
			break;
			case iconst_2:
			break;
			case iconst_3:
			break;
			case iconst_4:
			break;
			case iconst_5:
			break;
			case lconst_0:
			break;
			case lconst_1:
			break;
			case fconst_0:
			break;
			case fconst_1:
			break;
			case fconst_2:
			break;
			case dconst_0:
			break;
			case dconst_1:
			break;
			case bipush:
			break;
			case sipush:
			break;
			case ldc:
			break;
			case ldc_w:
			break;
			case ldc2_w:
			break;
			case iload:
			break;
			case lload:
			break;
			case fload:
			break;
			case dload:
			break;
			case alod:
			break;
			case iload_0:
			break;
			case iload_1:
			break;
			case iload_2:
			break;
			case iload_3:
			break;
			case lload_0:
			break;
			case lload_1:
			break;
			case lload_2:
			break;
			case lload_3:
			break;
			case fload_0:
			break;
			case fload_1:
			break;
			case fload_2:
			break;
			case fload_3:
			break;
			case dload_0:
			break;
			case dload_1:
			break;
			case dload_2:
			break;
			case dload_3:
			break;
			case aload_0:
			break;
			case aload_1:
			break;
			case aload_2:
			break;
			case aload_3:
			break;
			case iaload:
			break;
			case laload:
			break;
			case faload:
			break;
			case daload:
			break;
			case aaload:
			break;
			case baload:
			break;
			case caload:
			break;
			case saload:
			break;
			case istore:
			break;
			case lstore:
			break;
			case fstore:
			break;
			case dstore:
			break;
			case astore:
			break;
			case istore_0:
			break;
			case istore_1:
			break;
			case istore_2:
			break;
			case istore_3:
			break;
			case lstore_0:
			break;
			case lstore_1:
			break;
			case lstore_2:
			break;
			case lstore_3:
			break;
			case fstore_0:
			break;
			case fstore_1:
			break;
			case fstore_2:
			break;
			case fstore_3:
			break;
			case dstore_0:
			break;
			case dstore_1:
			break;
			case dstore_2:
			break;
			case dstore_3:
			break;
			case astore_0:
			break;
			case astore_1:
			break;
			case astore_2:
			break;
			case astore_3:
			break;
			case iastore:
			break;
			case lastore:
			break;
			case fastore:
			break;
			case dastore:
			break;
			case aastore:
			break;
			case bastore:
			break;
			case castore:
			break;
			case sastore:
			break;
			case pop:
			break;
			case pop2:
			break;
			case dup:
			break;
			case dup_x1:
			break;
			case dup_x2:
			break;
			case dup2:
			break;
			case dup2_x1:
			break;
			case dup2_x2:
			break;
			case swap:
			break;
			case iadd:
			break;
			case ladd:
			break;
			case fadd:
			break;
			case dadd:
			break;
			case isub:
			break;
			case lsub:
			break;
			case fsub:
			break;
			case dsub:
			break;
			case imul:
			break;
			case lmul:
			break;
			case fmul:
			break;
			case dmul:
			break;
			case idiv:
			break;
			case inst_ldiv:
			break;
			case fdiv:
			break;
			case ddiv:
			break;
			case irem:
			break;
			case lrem:
			break;
			case frem:
			break;
			case drem:
			break;
			case ineg:
			break;
			case lneg:
			break;
			case fneg:
			break;
			case dneg:
			break;
			case ishl:
			break;
			case lshl:
			break;
			case ishr:
			break;
			case lshr:
			break;
			case iushr:
			break;
			case lushr:
			break;
			case iand:
			break;
			case land:
			break;
			case ior:
			break;
			case lor:
			break;
			case ixor:
			break;
			case lxor:
			break;
			case iinc:
			break;
			case i2l:
			break;
			case i2f:
			break;
			case i2d:
			break;
			case l2i:
			break;
			case l2f:
			break;
			case l2d:
			break;
			case f2i:
			break;
			case f2l:
			break;
			case f2d:
			break;
			case d2i:
			break;
			case d2l:
			break;
			case d2f:
			break;
			case i2b:
			break;
			case i2c:
			break;
			case i2s:
			break;
			case lcmp:
			break;
			case fcmpl:
			break;
			case fcmpg:
			break;
			case dcmpl:
			break;
			case dcmpg:
			break;
			case ifeq:
			break;
			case ifne:
			break;
			case iflt:
			break;
			case ifge:
			break;
			case ifgt:
			break;
			case ifle:
			break;
			case if_icmpeq:
			break;
			case if_icmpne:
			break;
			case if_icmplt:
			break;
			case if_icmpge:
			break;
			case if_icmpgt:
			break;
			case if_icmple:
			break;
			case if_acmpeg:
			break;
			case if_acmpne:
			break;
			case inst_goto:
			break;
			case jsr:
			break;
			case ret:
			break;
			case tableswitch:
			break;
			case lookupswitch:
			break;
			case ireturn:
			break;
			case lreturn:
			break;
			case freturn:
			break;
			case dreturn:
			break;
			case areturn:
			break;
			case inst_return:
			break;
			case getstatic:
			break;
			case putstatic:
			break;
			case getfield:
			break;
			case putfield:
			break;
			case invokevirtual:
			break;
			case invokespecial:
			break;
			case invokestatic:
			break;
			case invokeinterface:
			break;
			case inst_new:
			break;
			case newarray:
			break;
			case anewarray:
			break;
			case arraylength:
			break;
			case athrow:
			break;
			case checkcast:
			break;
			case instanceof:
			break;
			case monitorenter:
			break;
			case monitorexit:
			break;
			case wide:
			break;
			case multianewarray:
			break;
			case ifnull:
			break;
			case ifnonnull:
			break;
			case goto_w:
			break;
			case jsr_w:
			break;





			default:
			break;
		}

		if(instrucoes[i].numarg>0){
			instrucoes[i].tipoarg = malloc(instrucoes[i].numarg*sizeof(int));
		}
		else{
			instrucoes[i].tipoarg = NULL;
		}
	}

	return(instrucoes);
}