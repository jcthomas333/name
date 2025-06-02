#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* HTD (char str[], int size)
{
    int *dec = (int *)malloc(size * sizeof(int));

    for(int i = 0; i < size; i++)
    {
        if(str[i] >= '0' && str[i] <= '9')
            dec[i] = str[i] - '0';
        else
        {
            switch(str[i])
            {
                case 'A': case 'a':
                    dec[i] = 10; break;
                case 'B': case 'b':
                    dec[i] = 11; break;
                case 'C': case 'c':
                    dec[i] = 12; break;
                case 'D': case 'd':
                    dec[i] = 13; break;
                case 'E': case 'e':
                    dec[i] = 14; break;
                case 'F': case 'f':
                    dec[i] = 15; break;
                default:
                    dec[i] = -1; break;
            }
        }
    }

    return dec;
}

char* DTB(int dec[],int size)
{
    char *bi = calloc(size * 4, sizeof(char));
    int f = 0;
    for(int i = 0; i < size; i++)
    {
        while(dec[i] > 0)
        {
            bi[f] = dec[i] % 2 - '0';
            dec[i] /= 2;
            f++;
        }
    }

    return bi;
}


int main() {
   char hex[] = "A9F6";
   int size = strlen(hex);

    int *result = HTD(hex, size);

    char *binary = DTB(result,size);


   for (int i = 0; i < size; i++) {
    printf("hex[%d] = %c → %d\n", i, hex[i], result[i]);
}

     
    //  for(int i = 0; i < size; i++) {
    //     printf("%c ", binary[i]);
    // }

    printf("\n");

    free(result);
    return 0;
}




