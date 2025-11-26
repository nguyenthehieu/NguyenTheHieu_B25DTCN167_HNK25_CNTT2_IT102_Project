#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAX_Products 100
#define MAX_Transaction 200

//nguyen mau ham
void addProduct();
void updateProduct();
void managementStatus();
void searchProduct();
void listProduct();
void sortingProduct();

int isEmpty(char str[]);
int isDuplicateId(char id[]); 
void toLowerCase(char str[]);

struct Product{
	char productId[10];   // ma hang hoa
	char name[50];     // ten hang hoa
	char unit[10];   // don vi
	int qty;      // so luong ton kho
	int status;   //trang thai(1:còn sd, 0: het han)
};

struct Transaction{ //Xuat/nhap hang
	char transId[20]; // Ma giao dich (Sinh ngau nhien hoac tu tang).
	char productId[10]; // Ma hang hoa
	char type[5];  //Kieu xuat/nhap (IN = nhap/ OUT = xuat).
	char date[15]; // Thoi gian giao dich.
};

struct Product prd[MAX_Products];
struct Transaction trans[MAX_Transaction];
int productCount = 0; // dem so hang hoa
int transCount = 0;

int main (){
	int choice;
	
	while(1){
	printf("\n+----------QUAN LY HANG HOA----------+\n");
	printf("1. Them ma hang moi.     	 	    \n");
	printf("2. Cap nhat thong tin.              \n");
	printf("3. Quan ly trang thai.   \n");
	printf("4. Tra cuu san pham.                \n");
	printf("5. Dang sach (Phan trang).          \n");
	printf("6. Sap xep danh sach.              \n");
	printf("7. Giao dich xuat/nhap hang hoa.    \n");
	printf("8. Lich su xuat/nhap.               \n");
	printf("+------------------------------------+\n");

	printf("\nMoi ban nhap lua chon: ");
	scanf("%d",&choice);
	
	switch(choice){
		case 1:
			addProduct();
			break;
		case 2:
			getchar();
			updateProduct();
			break;
		case 3:
			getchar();
			managementStatus();
			break;
		case 4:
			getchar();
			searchProduct();
			break;
		case 5:
			getchar();
			listProduct();
			break;
		case 6:
			getchar();
			sortingProduct();
			break;
		case 7:
			break;
		case 8:
			break;

		default:
			printf("Lua chon khong hop le. \n");
			return 0;
	}
	}
	return 0;
}

//kiem tra du lieu
int isEmpty(char str[]) { // kiem tra chuoi rong
    return strlen(str) == 0;
}

int isDuplicateId(char id[]) { // kiem tra trung nhau
    for (int i = 0; i < productCount; i++) {
        if (strcmp(prd[i].productId, id) == 0)
            return 1;
    }
    return 0;
}

//1. THEM SAN PHAM
void addProduct() {
    int amount;
	printf("<<----- THEM SAN PHAM ----->>\n");
    printf("Nhap so luong san pham muon them: ");
    scanf("%d", &amount);
    getchar();

    if (productCount + amount > MAX_Products) {
        printf("Kho da day. Khong the them.\n");
        return;
    }

    for (int i = 0; i < amount; i++) {
        printf("\n<<--- San pham %d --->>\n", productCount + 1);

        do {
            printf("Nhap ma san pham: ");
            fgets(prd[productCount].productId, 10, stdin);
            prd[productCount].productId[strcspn(prd[productCount].productId, "\n")] = '\0';

            if (isEmpty(prd[productCount].productId))
                printf("ID khong duoc trong\n");
            else if (isDuplicateId(prd[productCount].productId))
                printf("ID da ton tai, nhap ID khac!\n");
            else break;

        } while (1);

        do {
            printf("Nhap ten san pham: ");
            fgets(prd[productCount].name, 50, stdin);
            prd[productCount].name[strcspn(prd[productCount].name, "\n")] = '\0';

            if (isEmpty(prd[productCount].name))
                printf("Ten khong duoc de trong!\n");

        } while (isEmpty(prd[productCount].name));
        
        do {
            printf("Nhap don vi tinh: ");
            fgets(prd[productCount].unit, 10, stdin);
            prd[productCount].unit[strcspn(prd[productCount].unit, "\n")] = '\0';

            if (isEmpty(prd[productCount].unit))
                printf("Don vi tinh khong duoc de trong!\n");

        } while (isEmpty(prd[productCount].unit));

        do {
            printf("Nhap so luong ton kho: ");
            scanf("%d", &prd[productCount].qty);
            getchar();
            
            if (prd[productCount].qty < 0)
                printf("So luong phai >= 0!\n");

        } while (prd[productCount].qty < 0);

        prd[productCount].status = 1 ;
        productCount++;
    }

    printf("<<--- Them san pham thanh cong. --->>\n");
}

//2. CAP NHAT SAN PHAM
void updateProduct() {
	char id[10];
	printf("<<----- CAP NHAT SAN PHAM ----->>\n");
	printf("Nhap ma san pham can cap nhat: ");
	fgets(id,10,stdin);
	id[strcspn(id,"\n")]='\0';
	
	int found = -1;
	
	for(int i=0; i<productCount; i++){    //tim ID
		if( strcmp(id, prd[i].productId) == 0){
			found = i;
			break;
		}
	}	
	if (found == -1){
		printf("Khong tim thay.\n");
		return;
	}
	printf("<<--- CAP NHAT SAN PHAM --->>\n");
	
	
    do{
		printf("Nhap ten moi: ");
		char newName[50];
		fgets(newName, 50, stdin);
		newName[strcspn(newName, "\n")] = '\0';
	
		if(!isEmpty(newName)){
			strcpy(prd[found].name, newName);
	 		break;
	 	} else{
        	printf("Ten khong duoc de trong!\n");
		}
    } while(1);
	
	do{
		printf("Nhap don vi moi: ");
		char newUnit[10];
		fgets(newUnit, 10, stdin);
		newUnit[strcspn(newUnit, "\n")] ='\0';
		
		if(!isEmpty(newUnit)){
			strcpy(prd[found].unit, newUnit);
			break;
		} else {
        	printf("Don vi tinh khong duoc de trong!\n");	
		}	
	} while(1);
	
	do{
		printf("Nhap so luong moi: ");
		int newQty;
		scanf("%d",&newQty);
		getchar();
		if(newQty>=0){
			prd[found].qty = newQty;
			break;
		} else{
        	printf("So luong phai >= 0!\n");
        }
    
	} while(1);
	
	printf("<<---Cap nhat thanh cong--->>\n");
	}

//3. QUAN LY TRANG THAI
void managementStatus(){
	char id[10];
	printf("<<----- QUAN LY TRANG THAI ----->>\n");
	printf("Nhap ma san pham can doi trang thai: ");
	fgets(id,10,stdin);
	id[strcspn(id,"\n")]='\0';
	
	int found = -1;
	
	for(int i=0; i<productCount; i++){    //tim ID
		if( strcmp(id, prd[i].productId) == 0){
			found = i;
			break;
		}
	}	
	if (found == -1){
		printf("Khong ton tai trong danh sach.\n");
		return;
	}

	if(prd[found].status == 1){
		prd[found].status = 0;
		printf("<<---Cap nhat hang hoa thanh cong--->>\n");
	} else {
		printf("<<--- Hang hoa da bi khoa --->>\n");
	}
}

//4. TIM KIEM HANG HOA

// doi chuoi chu hoa thanh chu thuong
void toLowerCase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

void searchProduct(){
	char key[50];
	char keyLower[50], nameLower[50], idLower[10];
	
	printf("<<----- TIM KIEM HANG HOA ----->>\n");
	printf("Nhap ma hoac ten san pham can tim: ");
	fgets(key,50,stdin);
	key[strcspn(key,"\n")]='\0';
	
	if (isEmpty(key)) {
    	printf("Khong duoc de trong.\n");
    		return;
    }
    
	strcpy(keyLower, key);
	toLowerCase(keyLower);
	
	int found = 0;
	printf("\n<<--- Thong tin san pham --->>\n");
	printf("| %-10s | %-20s | %-8s | %-5s | %-12s |\n",
        "ID", "Ten SP", "Don vi", "SL", "Trang thai");
	
	for(int i=0; i<productCount; i++){ 
		strcpy(nameLower, prd[i].name);
		toLowerCase(nameLower);
		
		strcpy(idLower, prd[i].productId);
		toLowerCase(idLower);
		   
		if( strcmp(keyLower, idLower) == 0 || strstr(nameLower, keyLower) != NULL){
			printf("| %-10s | %-20s | %-8s | %-5d | %-12s |\n", prd[i].productId, prd[i].name, 
			prd[i].unit, prd[i].qty, prd[i].status == 1 ? "Con su dung" : "Het han");
			found = 1;
		} 
	}
	if(!found)
		printf("Khong tim thay thong tin nao.\n");	
	}

//5. DANH SACH (PHAN TRANG)
void listProduct(){
	if(productCount==0){
		printf("\nDang sach rong. Nhap hang hoa truoc.\n");
		return;
	}
	printf("<<------DANH SACH------>>\n");
	int page = 1;
	int perPage = 10;
	int index;
	
	while(1){
		index = (page - 1)*perPage;
		
		if(index>=productCount){
			printf("Het san pham.\n");
			return;
		}
		printf("------Trang %d-----\n", page);
		printf("| %-10s | %-20s | %-8s | %-5s | %-12s |\n",
               "ID", "Ten SP", "Don vi", "SL", "Trang thai");

		for(int i=index; i<index+perPage && i<productCount; i++){
			printf("| %-10s | %-20s | %-8s | %-5d | %-12s |\n", prd[i].productId, prd[i].name, 
			prd[i].unit, prd[i].qty, prd[i].status == 1 ? "Con su dung" : "Het han");
		} 
		int choice;
		printf("Xem tiep danh sach?\n 1. Co\n 2.Khong ");
		printf("\nLua chon cua ban: ");
		scanf("%d",&choice);
	
		if(choice == 1){
			printf("Nhap so trang muon xem: ");
			scanf("%d",&page);
			getchar();
		} else if(choice==2){
			printf("Dung xem dach sach.\n");
			return;
		} else {
			printf("Lua chon khong hop le.\n");
		}
	}
}

//6. SAP XEP
void sortingProduct(){
	int choice;
	
	if(productCount == 0){
		printf("Danh sach rong. Nhap hang hoa truoc.\n");
		return;
	}
	
	while(1){
		printf("Chon cach sap xep danh sach\n");
		printf("1. Sap xep theo ten \n");
		printf("2. Sap xep theo so luong\n");
		printf("Nhap lua chon: ");
		scanf("%d",&choice);
		getchar();
		
		if(choice == 1){
			for (int i = 0; i<productCount; i++){
				for( int j = i+1; j<productCount; j++){
					if(strcmp(prd[i].name,prd[j].name) > 0){
						struct Product temp = prd[i];
						prd[i] = prd[j];
						prd[j] = temp;
					}
				}	
			} 
			printf("<<---Sap xep thanh cong--->>\n");
			printf("<<------DANH SACH------>>\n");
			printf("| %-10s | %-20s | %-8s | %-5s | %-12s |\n",
               "ID", "Ten SP", "Don vi", "SL", "Trang thai");
			for(int i = 0; i<productCount; i++){
				printf("| %-10s | %-20s | %-8s | %-5d | %-12s |\n", prd[i].productId, prd[i].name, 
				prd[i].unit, prd[i].qty, prd[i].status == 1 ? "Con su dung" : "Het han");
			}	
			break;			
		} 
		else if(choice == 2){
			for (int i = 0; i<productCount; i++){
				for( int j = i+1; j<productCount; j++){
					if(prd[i].qty > prd[j].qty){
						struct Product temp = prd[i];
						prd[i] = prd[j];
						prd[j] = temp;
					}
				}	
			} 
			printf("<<---Sap xep thanh cong--->>\n");
			printf("<<------DANH SACH------>>\n");
			printf("| %-10s | %-20s | %-8s | %-5s | %-12s |\n",
               "ID", "Ten SP", "Don vi", "SL", "Trang thai");
			for(int i = 0; i<productCount; i++){
				printf("| %-10s | %-20s | %-8s | %-5d | %-12s |\n", prd[i].productId, prd[i].name, 
				prd[i].unit, prd[i].qty, prd[i].status == 1 ? "Con su dung" : "Het han");
				}
			break;
		} 
		else{ 
			printf("Lua chon khong hop le.\n");
		}
	}
}
