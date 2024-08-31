/*Kauane Micaelle Alves Barbosa de melo - kmabm@cesar.school

Construa uma calculadora programador didática (didática significa que deve ser
mostrado os passos na tela das operações efetuadas),  implementada na linguagem
C, que tenha as seguintes conversões 1 - de base 10 para: a)base 2, b) base 8,
c) base16,
d) código BCD Codificação binária decimal
2 - de base 10  para base com sinal com 16 bits, (complemento a 2)
3 - converter real em decimal para float e double, mostrando os respectivos bits
de sinal , expoente, expoente com viés e fração

Atualizações: 
Adicionado a função do Binario, Octal e Hexa 27/08/2024
Adicionado a função BCD - 30/08/2024 11:42
Adicionado a função do Complemento 2 - 30/08/2024 19:58
Adicionado a função Float e Double -  30/08/2024 22:39

    */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void imprimirPassoDivisao(int numero, int base, int resto) {
    printf("%d %% %d = %d (resto), %d / %d = %d (próximo valor)\n", 
           numero * base + resto, base, resto, numero * base + resto, base, numero);
}

void base10p2() {
    double num;
    printf("Digite um número decimal: ");
    scanf("%lf", &num);

    if (num == 0) {
        printf("O número binário é: 0000\n");
        return;
    }

    int sinal = (num < 0) ? -1 : 1;
    num = fabs(num);
    int inteiro = (int) num;
    double fracionario = num - inteiro;
    int *binario_inteiro = (int *) malloc(sizeof(int) * 32);
    int i = 0;

    printf("Convertendo a parte inteira para binário:\n");
    while (inteiro > 0) {
        binario_inteiro[i] = inteiro % 2;
        imprimirPassoDivisao(inteiro, 2, binario_inteiro[i]);
        inteiro /= 2;
        i++;
    }

    for (int j = 0; j < i / 2; j++) {
        int temp = binario_inteiro[j];
        binario_inteiro[j] = binario_inteiro[i - j - 1];
        binario_inteiro[i - j - 1] = temp;
    }

    char *binario_fracionario = (char *) malloc(sizeof(char) * 32);
    int k = 0;

    printf("Convertendo a parte fracionária para binário:\n");
    while (fracionario > 0 && k < 32) {
        fracionario *= 2;
        if (fracionario >= 1) {
            binario_fracionario[k] = '1';
            fracionario -= 1;
        } else {
            binario_fracionario[k] = '0';
        }
        printf("Multiplicando a parte fracionária por 2: %.15lf (parte fracionária atual)\n", fracionario);
        k++;
    }

    printf("O número binário é: ");
    if (sinal == -1) {
        printf("-");
    }
    for (int j = 0; j < i; j++) {
        printf("%d", binario_inteiro[j]);
    }
    printf(".");
    for (int j = 0; j < k; j++) {
        printf("%c", binario_fracionario[j]);
    }
    printf("\n");

    free(binario_inteiro);
    free(binario_fracionario);
}

void base10p8() {
    double num;
    printf("Digite um número decimal: ");
    scanf("%lf", &num);

    if (num == 0) {
        printf("O número octal é: 0000\n");
        return;
    }

    int sinal = (num < 0) ? -1 : 1;
    num = fabs(num);
    int inteiro = (int) num;
    double fracionario = num - inteiro;
    int *octal_inteiro = (int *) malloc(sizeof(int) * 32);
    int i = 0;

    printf("Convertendo a parte inteira para octal:\n");
    while (inteiro > 0) {
        octal_inteiro[i] = inteiro % 8;
        imprimirPassoDivisao(inteiro, 8, octal_inteiro[i]);
        inteiro /= 8;
        i++;
    }

    for (int j = 0; j < i / 2; j++) {
        int temp = octal_inteiro[j];
        octal_inteiro[j] = octal_inteiro[i - j - 1];
        octal_inteiro[i - j - 1] = temp;
    }

    char *octal_fracionario = (char *) malloc(sizeof(char) * 32);
    int k = 0;

    printf("Convertendo a parte fracionária para octal:\n");
    while (fracionario > 0 && k < 32) {
        fracionario *= 8;
        if (fracionario >= 1) {
            octal_fracionario[k] = (char)(fracionario) + '0';
            fracionario -= 1;
        } else {
            octal_fracionario[k] = '0';
        }
        printf("Multiplicando a parte fracionária por 8: %.15lf (parte fracionária atual)\n", fracionario);
        k++;
    }

    printf("O número octal é: ");
    if (sinal == -1) {
        printf("-");
    }
    for (int j = 0; j < i; j++) {
        printf("%d", octal_inteiro[j]);
    }
    printf(".");
    for (int j = 0; j < k; j++) {
        printf("%c", octal_fracionario[j]);
    }
    printf("\n");

    free(octal_inteiro);
    free(octal_fracionario);
}

void base10p16() {
    double num;
    printf("Digite um número decimal: ");
    scanf("%lf", &num);

    if (num == 0) {
        printf("O número hexadecimal é: 0000\n");
        return;
    }

    int sinal = (num < 0) ? -1 : 1;
    num = fabs(num);
    int inteiro = (int) num;
    double fracionario = num - inteiro;
    char *hex_inteiro = (char *) malloc(sizeof(char) * 32);
    int i = 0;

    printf("Convertendo a parte inteira para hexa:\n");
    while (inteiro > 0) {
        int resto = inteiro % 16;
        if (resto < 10) {
            hex_inteiro[i] = (char)(resto) + '0';
        } else {
            hex_inteiro[i] = (char)(resto - 10) + 'A';
        }
        imprimirPassoDivisao(inteiro, 16, resto);
        inteiro /= 16;
        i++;
    }

    for (int j = 0; j < i / 2; j++) {
        char temp = hex_inteiro[j];
        hex_inteiro[j] = hex_inteiro[i - j - 1];
        hex_inteiro[i - j - 1] = temp;
    }

    char *hex_fracionario = (char *) malloc(sizeof(char) * 32);
    int k = 0;

    printf("Convertendo a parte fracionária para hexa:\n");
    while (fracionario > 0 && k < 32) {
        fracionario *= 16;
        int resto = (int)fracionario;
        if (resto < 10) {
            hex_fracionario[k] = (char)(resto) + '0';
        } else {
            hex_fracionario[k] = (char)(resto - 10) + 'A';
        }
        fracionario -= resto;
        printf("Multiplicando a parte fracionária por 16: %.15lf (parte fracionária atual)\n", fracionario);
        k++;
    }

    printf("O número hexadecimal é: ");
    if (sinal == -1) {
        printf("-");
    }
    for (int j = 0; j < i; j++) {
        printf("%c", hex_inteiro[j]);
    }
    printf(".");
    for (int j = 0; j < k; j++) {
        printf("%c", hex_fracionario[j]);
    }
    printf("\n");

    free(hex_inteiro);
    free(hex_fracionario);
}
void base10pBCD(){
    double num;
        printf("Digite um número decimal: ");
        scanf("%lf", &num);

        if (num == 0) {
            printf("O número BCD é: 0000\n");
            return;
        }

        int sinal = (num < 0) ? -1 : 1;
        num = fabs(num);
        int inteiro = (int) num;

        char *bcd = (char *) malloc(sizeof(char) * 32);
        int i = 0;

        printf("Convertendo a parte inteira %d para BCD:\n", inteiro);
        while (inteiro > 0) {
            int digito = inteiro % 10;
            printf("Dígito: %d -> BCD: ", digito);
            for (int j = 3; j >= 0; j--) {
                bcd[i + j] = (digito % 2) ? '1' : '0';
                printf("%c", bcd[i + j]);
                digito /= 2;
            }
            printf("\n");
            i += 4;
            inteiro /= 10;
        }

        bcd[i] = '\0';

        for (int j = 0; j < i / 2; j++) {
            char temp = bcd[j];
            bcd[j] = bcd[i - j - 1];
            bcd[i - j - 1] = temp;
        }

        printf("O número BCD é: ");
        if (sinal == -1) {
            printf("-");
        }
        for (int j = 0; j < i; j++) {
            printf("%c", bcd[j]);
        }
        printf("\n");
        free(bcd);
}
void base10pComp2(){
        int n;
        printf("Digite um  número inteiro: ");
        scanf("%d", &n);

        if (n == 0) {
            printf("Número em complemento a 2 (16 bits): 0000 0000 0000 0000\n");
            return;
        }
        unsigned short num = (unsigned short) n;

        if (n < 0) {
            num = ~(-n - 1);  // inverte os bits usando o operador de negação btw
              //printf("oioi");
        }

        printf("Número em complemento a 2 (16 bits): ");
        for (int i = 15; i >= 0; i--) {
            printf("%d", (num >> i) & 1);
        }
        printf("\n");
    }
void printBinario(unsigned long long valor, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%llu", (valor >> i) & 1);
    }
}

void paraFloat(double num) {
    union {
        float f;
        unsigned int bits;
    } floatUnion;

    floatUnion.f = (float)num;

    unsigned int sinal = (floatUnion.bits >> 31) & 1; 
    unsigned int expoente = (floatUnion.bits >> 23) & 0xFF;
    unsigned int fracao = floatUnion.bits & 0x7FFFFF;

    printf("Real convertido:\n");
    printf("Float: %f\n", floatUnion.f);
    printf("Sinal: ");
    printBinario(sinal, 1);
    printf("\n");

    printf("Expoente: %u \n ", expoente);
    printf("%u",expoente - 127);
    printf(" + 127 = %u \n", expoente - 127);
    printBinario(expoente, 8);
    //printf("teste");

    printf("\nFração: ");
    printBinario(fracao, 23);
    printf("\n");

    printf("Representação: \n");
    printBinario(floatUnion.bits, 32);
    printf("\n\n");
}

void paraDouble(double num) {
    union {
        double d;
        unsigned long long bits;
    } doubleUnion;

    doubleUnion.d = num;

    unsigned long long sinal = (doubleUnion.bits >> 63) & 1; 
    unsigned long long expoente = (doubleUnion.bits >> 52) & 0x7FF;
    unsigned long long fracao = doubleUnion.bits & 0xFFFFFFFFFFFFF;

    printf("Real convertido:\n");
    printf("Double: %lf\n", doubleUnion.d);

    printf("Sinal: ");
    printBinario(sinal, 1);
    printf("\n");

    printf("Expoente: %llu \n ", expoente);
    printf("%llu",expoente - 1023);
    printf(" + 1023 = %lld \n", expoente - 1023);
    printBinario(expoente, 11);

    printf("\nFração: ");
    printBinario(fracao, 52);
    printf("\n");

    printf("Representação: \n");
    printBinario(doubleUnion.bits, 64);
    printf("\n\n");
    //printf("teste")
}

int menu() {
    int escolha;
    printf("Menu:\n");
    printf("1. Base 10 para Base 2\n");
    printf("2. Base 10 para Base 8\n");
    printf("3. Base 10 para Base 16\n");
    printf("4. Base 10 para BCD\n");
    printf("5. Complemento a 2 com 16 bits\n");
    printf("6. Converter para float\n");
    printf("7. Converter para double\n");
    printf("0. Sair\n");
    printf("Digite sua opção: ");
    scanf("%d", &escolha);
    return escolha;
}

int main(void) {
    int escolha;
    double num;

    do {
        escolha = menu();
        if (escolha == 1) {
            base10p2();
        } else if (escolha == 2) {
            base10p8();
        } else if (escolha == 3) {
            base10p16();        
        } else if (escolha == 4) {
            base10pBCD();
        } else if (escolha == 5) {
            base10pComp2();
        } else if (escolha == 6) {
            printf("Digite um número real: ");
            scanf("%lf", &num);
            paraFloat(num);
        } else if (escolha == 7) {
            printf("Digite um número real: ");
            scanf("%lf", &num);
            paraDouble(num);
        } else if (escolha == 0) {
            printf("Saindo..\n");
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 0);

    return 0;
}