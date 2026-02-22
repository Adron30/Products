// Bin?
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[100];
    int quant;
    float price;
} Product;

int main() {
    Product myProduct;
    Product ExistingProduct;
    char tempStorage[MAX];
    FILE* fpbin = NULL;
    int productFound = 0;

    fpbin = fopen("prods.bin", "rb+");

    if (fpbin == NULL) {
        printf("Can't open file\n");
    } else {
        printf("ADD/MODIFY PRODUCT\n");
        printf("Name of the product: ");
        fgets(myProduct.name, MAX, stdin);
        myProduct.name[strlen(myProduct.name) - 1] = '\0';

        if (strcmp(myProduct.name, "ls") == 0) { //Using for debugging mainly
            fread(&ExistingProduct, sizeof(Product), 1, fpbin);
            while (!feof(fpbin)) {
                printf("%s, %.2fE, Stock: %d unit(s)\n", ExistingProduct.name, ExistingProduct.price, ExistingProduct.quant);
                fread(&ExistingProduct, sizeof(Product), 1, fpbin);
            }
        } else {
            //Managin user input
            printf("How many new units of this product there are: ");
            fgets(tempStorage, MAX, stdin);
            tempStorage[strlen(tempStorage) - 1] = '\0';
            myProduct.quant = atoi(tempStorage);
            printf("Price of the product: ");
            fgets(tempStorage, MAX, stdin);
            tempStorage[strlen(tempStorage) - 1] = '\0';
            myProduct.price = atof(tempStorage);

            //Actually adding things
            fread(&ExistingProduct, sizeof(Product), 1, fpbin);
            while (!feof(fpbin)) {
                if (strcmp(ExistingProduct.name, myProduct.name) == 0) {
                    productFound = 1;
                    myProduct.quant = myProduct.quant + ExistingProduct.quant;
                    fseek(fpbin, sizeof(Product) * -1, SEEK_CUR);
                    fwrite(&myProduct, sizeof(Product), 1, fpbin);
                    printf("\nProduct found and updated!\n");
                    fseek(fpbin, sizeof(Product) * 1, SEEK_END); //Go the end if product was found
                } else {
                    printf("\n%s, %.2fE, Stock: %d unit(s)", ExistingProduct.name, ExistingProduct.price, ExistingProduct.quant);
                }
                fread(&ExistingProduct, sizeof(Product), 1, fpbin);
            }
            if (productFound == 0) {
                printf("\n");
                printf("Product was not found. Adding it to the list.");
                fseek(fpbin, 0, SEEK_END);
                fwrite(&myProduct, sizeof(Product), 1, fpbin);
            }
            fclose(fpbin);
        }
    }

    return 0;
}