#include  <stdio.h>
#include <string.h>

typedef struct {
    char name[100];
    int quant;
    float price;
} Product;



int main(){

    Product myProduct;
    strcpy(myProduct.name, "Milk");
    myProduct.quant = 10;
    myProduct.price = 2.5;



    FILE *fpbin = NULL;

    fpbin = fopen("prods.bin", "w");

    if (fpbin == NULL){
        printf("Can't open File");
    } else {
    fwrite(&myProduct, sizeof(Product), 1, fpbin);
    printf("File restored\n");

    }
    

    return 0;
}