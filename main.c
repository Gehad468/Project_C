#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
char k;
COORD coord= {0,0};


void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
struct Product
{
    char Name_p[30];
    float Price_p;
    int Quantiy_p;

};
typedef struct Product Product;
struct Category
{
    int prd_count;
    char Name_C[30];
    Product *New_Product;
    int max_product;
};
typedef struct Category Category;
struct Store
{
    Category *category;
    int cat_count;
    int max_category;
};
typedef struct Store Store;
//initial
void initial(Store *str1)
{
    str1->cat_count = 2;
    str1->max_category = 2;

    str1->category = (Category *)malloc(str1->max_category * sizeof(Category));

    for (int i = 0; i < 2; i++)
    {
        str1->category[i].prd_count = 2;
        str1->category[i].New_Product = (Product *)malloc(str1->category[i].prd_count * sizeof(Product));
        str1->category[i].max_product = str1->category[i].prd_count+20;
    }

    strcpy(str1->category[0].Name_C, "Electronics");
    strcpy(str1->category[1].Name_C, "Clothes");

    strcpy(str1->category[0].New_Product[0].Name_p, "Phone");
    strcpy(str1->category[0].New_Product[1].Name_p, "Laptop");
    strcpy(str1->category[1].New_Product[0].Name_p, "T-Shirt");
    strcpy(str1->category[1].New_Product[1].Name_p, "Blouse");

    str1->category[0].New_Product[0].Price_p = 7000;
    str1->category[0].New_Product[1].Price_p = 17000;
    str1->category[1].New_Product[0].Price_p = 500;
    str1->category[1].New_Product[1].Price_p = 600;

    str1->category[0].New_Product[0].Quantiy_p = 10;
    str1->category[0].New_Product[1].Quantiy_p = 5;
    str1->category[1].New_Product[0].Quantiy_p = 4;
    str1->category[1].New_Product[1].Quantiy_p = 6;
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void display( Store *str1)
{        SetColor(9);
    for(int cat=0; cat<str1->cat_count; cat++)
    {
        printf("\n\n***************************^^^^^********************************\n");
        printf("\nCategory %d : %s",cat+1,str1->category[cat].Name_C);

        for(int prd=0; prd<str1->category[cat].prd_count; prd++)
        {
           SetColor(7);
            printf("\nProduct %d :\tName: %s\tPrice: %.2f\tQuantity: %d",prd+1,str1->category[cat].New_Product[prd].Name_p,str1->category[cat].New_Product[prd].Price_p,str1->category[cat].New_Product[prd].Quantiy_p);
            SetColor(9);
        }

    }
}

void add_cat(Store *str1)
{
    int categoryExists;
    Category new_Cat;
    char k;

    do
    {
        do
        {
            categoryExists = 0;
            printf("Enter Category Name\n");
            scanf(" %[^\n]s", new_Cat.Name_C) ;


            for (int i = 0; i < str1->cat_count; i++)
            {
                if (strcmp(new_Cat.Name_C, str1->category[i].Name_C) == 0)
                {
                    categoryExists = 1;
                    SetColor(14);
                    printf("Category with the same name already exists. Please enter a different name.\n");
                    SetColor(7);
                    break;
                }
            }
        }
        while (categoryExists);

        if (str1->cat_count == str1->max_category)
        {
            str1->max_category += 10;
            str1->category = (Category *)realloc(str1->category, str1->max_category * sizeof(Category));
        }

        new_Cat.max_product = 30;
        new_Cat.New_Product = (Product *)malloc(new_Cat.max_product * sizeof(Product));
        new_Cat.prd_count = 0;
        SetColor(12);
        printf("Do you want to add a product to this category? (y/n): ");
        SetColor(7);
        char choisechar;
        scanf(" %c", &choisechar);

        if (choisechar == 'y' || choisechar == 'Y')
        {
            do
            {
                if (new_Cat.prd_count == new_Cat.max_product)
                {
                    new_Cat.max_product += 10;
                    new_Cat.New_Product = (Product *)realloc(new_Cat.New_Product, new_Cat.max_product * sizeof(Product));
                }
                printf("Enter New_Product_Name\n");
                scanf(" %[^\n]s", new_Cat.New_Product[new_Cat.prd_count].Name_p);
                printf("Enter New_Product_Price\n");
                do
                {
                    if (scanf("%f", &new_Cat.New_Product[new_Cat.prd_count].Price_p) == 1)
                    {
                        break;
                    }
                    else
                    {
                        SetColor(4);
                        printf("Error!!\nPlease Enter a valid Price!!\n");
                        SetColor(7);

                        while (getchar() != '\n')
                            ;
                    }
                }
                while (1);

                printf("Enter New_Product_Quantity\n");
                do
                {
                    if (scanf("%d", &new_Cat.New_Product[new_Cat.prd_count].Quantiy_p) == 1)
                    {
                        break;
                    }
                    else
                    {
                        SetColor(4);

                        printf("Error!!\nPlease Enter a valid Quantity!!\n");
                        SetColor(7);

                        while (getchar() != '\n');
                    }
                }
                while (1);
                new_Cat.prd_count++;
                SetColor(2);
                printf("Product added successfully!\n");
                SetColor(12);
                printf("Do you want to add another product? (y/n): ");
                SetColor(7);
                scanf(" %c", &choisechar);

            }
            while (choisechar == 'y' || choisechar == 'Y');
        }

        str1->category[str1->cat_count] = new_Cat;
        str1->cat_count++;
        SetColor(2);
        printf("Category added successfully!\n");
        SetColor(12);
        printf("Do you want to add another Category? (y/n): ");
        SetColor(7);
        scanf(" %c", &k);

    }
    while (k == 'y' || k == 'Y');
}

void add_product(Store *str)
{
    char categoryName[30], PrdName[30], k;
    float priceProd;
    int quantityProd;
    int categoryIndex = -1;

    do
    {
        printf("Enter the category Name to add the product: ");
        scanf(" %[^\n]s", categoryName);

        for (int i = 0; i < str->cat_count; i++)
        {
            if (strcmp(categoryName, str->category[i].Name_C) == 0)
            {
                categoryIndex = i;
                break;
            }
        }

        if (categoryIndex < 0 || categoryIndex >= str->cat_count)
        {
            SetColor(4);
            printf("Invalid category. Please try again.\n");
            SetColor(7);
        }
    }
    while (categoryIndex < 0 || categoryIndex >= str->cat_count);

    do
    {
        int idexpor = -1;
        printf("Enter New_Product_Name\n");
        scanf(" %[^\n]s", PrdName);

        for (int i = 0; i < str->category[categoryIndex].prd_count; i++)
        {
            if (strcmp(str->category[categoryIndex].New_Product[i].Name_p, PrdName) == 0)
            {
                idexpor = i;
                break;
            }
        }

        if (idexpor != -1)
        {
            SetColor(14);
            printf("The Product already Exists\n");
            SetColor(7);
            printf("Enter The Quantity Please\n");

            do
            {
                if (scanf("%d", &quantityProd) == 1)
                {
                    break;
                }
                else
                {
                    SetColor(4);
                    printf("Error!!\nPlease Enter a valid Quantity!!\n");
                    SetColor(7);

                    while (getchar() != '\n');
                }
            }
            while (1);

            str->category[categoryIndex].New_Product[idexpor].Quantiy_p += quantityProd;
        }
        else
        {
            if (str->category[categoryIndex].prd_count == str->category[categoryIndex].max_product)
            {
                str->category[categoryIndex].max_product += 10;
                str->category[categoryIndex].New_Product = realloc(str->category[categoryIndex].New_Product, str->category[categoryIndex].max_product * sizeof(Product));
            }

            printf("Enter New_Product_Price\n");
            scanf("%f", &priceProd);

            printf("Enter New_Product_Quantity\n");

            do
            {
                if (scanf("%d", &quantityProd) == 1)
                {
                    break;
                }
                else
                {
                    SetColor(4);
                    printf("Error!!\nPlease Enter a valid Quantity!!\n");
                    SetColor(7);
                    while (getchar() != '\n');
                }
            }
            while (1);

            strcpy(str->category[categoryIndex].New_Product[str->category[categoryIndex].prd_count].Name_p, PrdName);
            str->category[categoryIndex].New_Product[str->category[categoryIndex].prd_count].Price_p = priceProd;
            str->category[categoryIndex].New_Product[str->category[categoryIndex].prd_count].Quantiy_p = quantityProd;
            str->category[categoryIndex].prd_count++;
        }
        SetColor(2);
        printf("Product added successfully!\n");
        SetColor(12);
        printf("Do You Want To Add A New Product? Press (y/n)\n");
        SetColor(7);

        scanf(" %c", &k);

    }
    while (k == 'y' || k == 'Y');
}



void remove_Product(Store * str)
{

    char categ_name[30],prod_name[30];
    int categoryIndex = -1;
    do
    {
        printf("Enter the category Name to Remove its product\n");
        scanf(" %[^\n]s",categ_name);
        for (int i = 0; i < str->cat_count; i++)
        {
            if (strcmp(categ_name, str->category[i].Name_C) == 0)
            {
                categoryIndex = i;
                break;
            }
        }
        if (categoryIndex < 0 || categoryIndex >= str->cat_count)
        {
            SetColor(4);
            printf("Invalid category. Please try again.\n");
            SetColor(7);

        }

    }

    while(categoryIndex < 0 || categoryIndex >= str->cat_count);
    if(str->category[categoryIndex].prd_count==0)
    {
        SetColor(14);
        printf("there is no Products here yet :(");
        SetColor(7);
        return ;
    }
    int prodIndex=-1;
    printf("Pls Enter The Product\n");
    scanf(" %[^\n]s",prod_name);
    if(categoryIndex!=-1)
    {
        for(int i=0; i<str->category[categoryIndex].prd_count; i++)
        {
            if(strcmp(str->category[categoryIndex].New_Product[i].Name_p,prod_name)==0)
            {
                prodIndex=i;
                break;
            }
        }

        if(prodIndex!=-1)
        {
            for(int i=prodIndex; i<str->category[categoryIndex].prd_count-1; i++)
            {
                str->category[categoryIndex].New_Product[i]=str->category[categoryIndex].New_Product[i+1];
            }
            str->category[categoryIndex].prd_count--;
            if(str->category[categoryIndex].prd_count>0)
            {
                str->category[categoryIndex].New_Product = realloc(str->category[categoryIndex].New_Product, str->category[categoryIndex].prd_count *sizeof(Product));
            }
            SetColor(2);
            printf("The Product removed Successfully (:\n");
            SetColor(7);

        }
        else
        {
            SetColor(14);
            printf("There is no Product with this Name to remove it ):\n");
            SetColor(7);


        }
    }

}

void Move_product(Store *str)
{
    char sourceCategory[30], destinationCategory[30], productName[30];
    int sourceCategoryIndex = -1, destinationCategoryIndex = -1;
    int prodIndex=-1;
    do
    {
        printf("Enter the source category name: ");
        scanf(" %[^\n]s", sourceCategory);
        for (int i = 0; i < str->cat_count; i++)
        {
            if (strcmp(sourceCategory, str->category[i].Name_C) == 0)
            {
                sourceCategoryIndex = i;
                break;
            }
        }
        if (sourceCategoryIndex < 0 || sourceCategoryIndex >= str->cat_count)
        {
            SetColor(14);
            printf("Invalid category. Please try again.\n");
            SetColor(7);

        }

    }
    while (sourceCategoryIndex < 0 || sourceCategoryIndex >= str->cat_count);

    do
    {
        printf("Enter the destination category name: ");
        scanf(" %[^\n]s", destinationCategory);
        for (int i = 0; i < str->cat_count; i++)
        {
            if (strcmp(destinationCategory, str->category[i].Name_C) == 0)
            {
                destinationCategoryIndex = i;
                break;
            }
        }
        if (destinationCategoryIndex < 0 || destinationCategoryIndex >= str->cat_count)
        {
            SetColor(14);
            printf("Invalid category. Please try again.\n");
            SetColor(7);
        }

    }
    while (destinationCategoryIndex < 0 || destinationCategoryIndex >= str->cat_count);

    printf("Enter the product name to move: ");
    scanf(" %[^\n]s", productName);
    for (int i = 0; i < str->category[sourceCategoryIndex].prd_count; i++)
    {
        if (strcmp(str->category[sourceCategoryIndex].New_Product[i].Name_p, productName) == 0)
        {
            prodIndex = i;
            break;
        }
    }
    if(prodIndex!=-1)
    {

        if (str->category[destinationCategoryIndex].prd_count < str->category[destinationCategoryIndex].max_product)
        {
            strcpy(str->category[destinationCategoryIndex].New_Product[str->category[destinationCategoryIndex].prd_count].Name_p,
                   str->category[sourceCategoryIndex].New_Product[prodIndex].Name_p);
            str->category[destinationCategoryIndex].New_Product[str->category[destinationCategoryIndex].prd_count].Price_p =
                str->category[sourceCategoryIndex].New_Product[prodIndex].Price_p;
            str->category[destinationCategoryIndex].New_Product[str->category[destinationCategoryIndex].prd_count].Quantiy_p =
                str->category[sourceCategoryIndex].New_Product[prodIndex].Quantiy_p;
            str->category[destinationCategoryIndex].prd_count++;
            if (str->category[sourceCategoryIndex].prd_count > 0)
            {

                for (int i = prodIndex; i < str->category[sourceCategoryIndex].prd_count - 1; i++)
                {
                    strcpy(str->category[sourceCategoryIndex].New_Product[i].Name_p,
                           str->category[sourceCategoryIndex].New_Product[i + 1].Name_p);
                    str->category[sourceCategoryIndex].New_Product[i].Price_p =
                        str->category[sourceCategoryIndex].New_Product[i + 1].Price_p;
                    str->category[sourceCategoryIndex].New_Product[i].Quantiy_p =
                        str->category[sourceCategoryIndex].New_Product[i + 1].Quantiy_p;
                }
                str->category[sourceCategoryIndex].prd_count--;
            }
            SetColor(2);
            printf("Product moved successfully!\n");
            SetColor(7);

        }
        else
        {
            str->category[destinationCategoryIndex].max_product+=10;
            str->category[destinationCategoryIndex].New_Product=realloc(str->category[destinationCategoryIndex].New_Product,str->category[destinationCategoryIndex].max_product*sizeof(Product));

        }
    }
    else
    {
        SetColor(4);
        printf("There is No Product With this Name Here \":\"");
        SetColor(7);
    }
}
float PriceInvice;
void Sell_invoice(Store * str)
{

    printf("\n");
    do
    {
        printf("Enter Your Product To Sell it\n");
        char productName[30];
        scanf(" %[^\n]s",productName);
        printf("Enter Your Quantity To Sell Product\n");
        int quantity;
        do
        {
            if(  scanf("%d",&quantity)==1)
            {
                break;
            }
            else
            {
                SetColor(4);
                printf("Error!!\nPlease Enter a valid Quantity!!\n");
                SetColor(7);
                while(getchar()!='\n');
            }
        }
        while(1);

        int productfound = 0;
        float TotalPrice=0;
        int TotalQuan=0;
        for (int i = 0; i < str->cat_count; i++)
        {
            for (int j = 0; j < str->category[i].prd_count; j++)
            {
                if (strcmp(str->category[i].New_Product[j].Name_p, productName) == 0)
                {
                    productfound = 1;

                    if (str->category[i].New_Product[j].Quantiy_p>= quantity)
                    {
                        str->category[i].New_Product[j].Quantiy_p -= quantity;

                        printf("\n>===========***Invoice***===========<\n");
                        printf("\nProduct Name:       %s",productName);
                        printf("\nProduct Quantity:   %d",quantity);
                        printf("\nProduct Price:      %.2f EG",str->category[i].New_Product[j].Price_p);
                        TotalQuan= str->category[i].New_Product[j].Quantiy_p;
                        TotalPrice=quantity*str->category[i].New_Product[j].Price_p;
                        PriceInvice+=TotalPrice;
                        printf("\nRemaining Quantity: %d",TotalQuan);
                        printf("\nTotla Price:        %.2f EG",TotalPrice);
                        SetColor(7);
                    }
                    else
                    {
                        SetColor(4);
                        printf("Insufficient quantity available for %s.\n", productName);
                        SetColor(7);
                    }

                    break;
                }
            }

            if (productfound)
            {
                break;
            }
        }

        if (!productfound)
        {
            SetColor(14);
            printf("Product not found: %s\n", productName);
            SetColor(4);
        }
        SetColor(12);
        printf("\nDo You Want To add Another Product? Press (y/n)\n");
        SetColor(7);

        scanf(" %c", &k);
        if(k=='n'||k=='N')
        {
            SetColor(11);
            printf("The Total Price of the all products = %.2f",PriceInvice);
            SetColor(7);
        }
    }
    while (k == 'y' || k == 'Y');
}
void freeMemory(Store *str1)
{
    for(int i=0; i<str1->cat_count; i++)
        free(str1->category[i].New_Product);
    free(str1->category);
}
int main()
{
    int id;
    Store str;
    initial(&str);


    char menu[8][30]= {"1) Add Product\n","2) Add Category \n","3) Remove Product\n","4) Display\n","5) Move Product\n", "6) Make selling invoice\n","7) Exit!" };
    do
    {
        for(int i=0; i<7; i++)
        {
            gotoxy(85,i+15);
            if(i==id)
            {
                SetColor(3);
            }
            else
            {
                SetColor(10);
            }
            printf("%s",menu[i]);
        }
        char key=getch();
        system("cls");
        if(key==-32)
        {
            key=getch();

            if(key==71)
            {
                id=0;
            }
            else if(key==79)
            {
                id=6;
            }
            else if(key==72)
            {
                if(id!=0)
                {
                    id--;
                }
            }
            else if(key==80)
            {
                if(id!=6)
                {
                    id++;
                }
            }
        }
        else
        {
            if(key==13)
            {
                switch(id)
                {
                case 0:

                    add_product(&str);
                    break;
                case 1:
                    add_cat(&str);
                    break;
                case 2:
                    remove_Product(&str);
                    break;
                case 3:
                    display(&str);
                    break;
                case 4:
                    Move_product(&str);
                    break;
                case 5:
                    Sell_invoice(&str);
                    break;
                case 6:
                    printf("Thanks For You!\n");
                    exit(0);
                }
            }
            else if(key==27)
            {
                exit(0);
            }
        }
    }
    while(id<7);
    freeMemory(&str);
    return 0;
}
