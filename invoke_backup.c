void invokestatic_impl(frame *f, u1 indexbyte1, u1 indexbyte2){

	u2 indice_cp = (indexbyte1 << 8) | indexbyte2;
	char *nomemetodo = obterNomeMetodo(f->cp,indice_cp,0);
	char *descriptormetodo = obterDescriptorMetodo(f->cp,indice_cp,0);
	printf("Vai rodar invoke static...\n");
	if(resolverMetodo(f->cp,indice_cp,0)){
		int *parametros_cont = malloc(sizeof(int));
		char *classeNova = obterClasseDoMetodo(f->cp,indice_cp);
		method_info * methodAux = BuscarMethodClasseCorrente_classes(jvm->classes, classeNova, nomemetodo);
		attribute_info *aux;
		int posicao;
		for(posicao = 0; posicao < methodAux->attributes_count; posicao++) {
			aux = (*(methodAux->attributes+posicao));
			classesCarregadas *classeAtual = BuscarElemento_classes(jvm->classes,classeNova);
			char *nameindex = decodificaStringUTF8(classeAtual->arquivoClass->constant_pool-1+aux->attribute_name_index);
			if(strcmp(nameindex,"Code")==0){
				code_attribute *c = (code_attribute *) aux->info;
				frame *f_novo = criarFrame(classeNova,c->max_locals);
				f_novo = transferePilhaVetor(f,f_novo,parametros_cont);
				jvm->frames = Push_frames(jvm->frames,f_novo);
				// printf("%lu\n",sizeof(vetor_locais));
				for(int i=0;i<*(parametros_cont);i++){
					printf("VARIÁVEL LOCAL: %04x\n",*(jvm->frames->topo->f->v[i].variavel));
				}

				printf("Classe nova: %s\n",classeNova);
				classesCarregadas *classe = BuscarElemento_classes(jvm->classes,classeNova);
				if (classe != NULL) {
					printf("Buscou a classe carregada...\n");
				}

				// Achar o método na classe que o contém
				method_info *metodos = classe->arquivoClass->methods;
				for(method_info *aux=metodos;aux<metodos+classe->arquivoClass->methods_count;aux++){
					// Verificar se o nome e o descriptor do método que deve ser invocado são iguais ao que está sendo analisado no .class
					char * nomeMetodoAux = decodificaStringUTF8(classe->arquivoClass->constant_pool-1+aux->name_index);
					char * descriptorMetodoAux = decodificaStringUTF8(classe->arquivoClass->constant_pool-1+aux->descriptor_index);

					if(strcmp(nomemetodo,nomeMetodoAux) == 0 && strcmp(descriptormetodo,descriptorMetodoAux) == 0){
						printf("Metodo da classe: %s\n",nomeMetodoAux);
						// Executar o code do método invocado
						printf("Executando método...\n");
						executarMetodo(aux,classeNova,2);

					}
				}

			}
		}
	}
}
