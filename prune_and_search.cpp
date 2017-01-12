#include <stdio.h>
#include <stdlib.h>

void prune(int *data, int input, int total){
	int is_divisible = 0;
	
	int count = 0;
	if(total<=8){
		int min = data[0];
		int count_temp = 0;
		while(1){
			min = data[0];
			for(int i=0;i<total;i++){
				if(min>data[i]){
					min = data[i];
				}
			}
			printf("min=%d\n",min);
			count_temp += 1;
			if(count_temp==input){
				break;
			}
			for(int i=0;i<total;i++){
				if(min==data[i]){
					data[i] = 9999999;
					printf("i==%d\n",i);
					break;
				}
			}
//			for(int i=0;i<total;i++){
//				printf("%d ",data[i]);
//			}			
			
		}
		printf("%d",min);
		printf("\n");
		return;
	}
	is_divisible = total % 5;
	int number = 0; // 全部有幾個一組 
	if(is_divisible == 0)
	    number = total / 5;
	else{
		number = total / 5 + 1;
	}
	int data2[600][5] = {-1};
	for(int i=0;i<number;i++){
		for(int j=0;j<5;j++){
			if(count<total){
				data2[i][j] = data[count];
				count++;
			}
			else{
				data2[i][j] = 9999999;
			}
		}
	}
	
	for(int i=0;i<number;i++){
		for(int j=0;j<5;j++){
			printf("%d ",data2[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	
	// bubble sort each
	for(int u=0;u<number;u++){
		for (int q=4;q>=0;q--)
	    {
	        for (int w=0;w<=q-1;w++)
	        {
	            if (data2[u][w] > data2[u][w + 1])
	            {
	            	int temp=0;
	                temp = data2[u][w];
					data2[u][w] = data2[u][w + 1];
					data2[u][w+1] = temp;
					
	            }
	        }
    	}
	}
	
	for(int i=0;i<number;i++){
		for(int j=0;j<5;j++){
			printf("%d ",data2[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	
	// bubble sort median
	for (int q=number-1;q>=0;q--)
    {
        for (int w=0;w<q-1;w++)
        {
            if (data2[w][2] > data2[w+1][2])
            {
            	int temp[1][5]={0};
                temp[0][0] = data2[w][0];
                temp[0][1] = data2[w][1];
                temp[0][2] = data2[w][2];
                temp[0][3] = data2[w][3];
                temp[0][4] = data2[w][4];
				data2[w][0] = data2[w+1][0];
				data2[w][1] = data2[w+1][1];
				data2[w][2] = data2[w+1][2];
				data2[w][3] = data2[w+1][3];
				data2[w][4] = data2[w+1][4];
				data2[w+1][0] = temp[0][0];
				data2[w+1][1] = temp[0][1];
				data2[w+1][2] = temp[0][2];
				data2[w+1][3] = temp[0][3];
				data2[w+1][4] = temp[0][4];
            }
        }
	}
	
	for(int i=0;i<number;i++){
		for(int j=0;j<5;j++){
			printf("%d ",data2[i][j]);
		}
		printf("\n");
	}
	
	
	int median = (number - 1) / 2;
	int median_s = data2[median][2];
	int num_s1 = median*3 + 2;
	int num_s2 = 1;
	int num_s3 = ( (number - 1) - median ) * 3 + 2;
	int data_s1[3000] = {-1};
	int count_s1=0;
	int data_s2[3000] = {-1};
	int count_s2=0;
	int data_s3[3000] = {-1};
	int count_s3=0;
	
	for(int i=0;i<number;i++){
		for(int j=0;j<5;j++){
			if( (i < median && j>=0 && j<=2) || (i==median && j>=0 && j<2) ){ // 左上 
				data_s1[count_s1] = data2[i][j];
				count_s1++;
			}else if( (i > median && j>=2 && j<5) || (i==median && j>2 && j<5) ){ //右上 
				data_s3[count_s3] = data2[i][j];
				count_s3++;
			}else if( (i == median && j==2) ){ // S2
				data_s2[count_s2] = data2[i][j];
				count_s2++;
			}else{
				if(data2[i][j] < median_s){ // if < s2 
					data_s1[count_s1] = data2[i][j];
					count_s1++;
				}else if(data2[i][j] == median_s){ // if == s2 
					data_s2[count_s2] = data2[i][j];
					count_s2++;
				}else{ // if > s2 
					data_s3[count_s3] = data2[i][j];
					count_s3++;
				}
			}
		}
	}
	
	if( count_s1 >= input ){
		printf("\ncase1\n");
		printf("count_s1=%d\n", count_s1);
		for(int i=0;i<count_s1;i++){
			printf("%d ",data_s1[i]);
		}
		prune(data_s1,input,count_s1);
	}else if( count_s1 + count_s2 >= input ){
		printf("\ncase2\n");
		printf("%d",median_s);
		printf("\n");
		return ;
	}else{
		printf("\ncase3\n");
		input = input-count_s1-count_s2;
		printf("input = %d\n",input);
		printf("count_s3=%d\n", count_s3);
//		for(int i=0;i<count_s3;i++){
//			printf("%d ",data_s3[i]);
//		}
		prune(data_s3,input,count_s3);
	}
	
	
	
	
}

int main(){
	FILE *datain;
	datain = fopen("input5.txt","r");
	int data[3000]={-1};
	if(!datain)
	{
		printf("data not exist");
        system("PAUSE");
        return 0;
	}
	int cnt=0;
	while(fscanf(datain,"%d",&data[cnt])!=EOF){
		cnt++;
	}
	//cout<<cnt;
	fclose(datain);
	
//	for(int i=0;i<cnt;i++){
//		printf("%d ", data[i]);
//	}
	
	
	while(1){
		printf("input k (input 0 to exit): ");
		int input=0;
		scanf("%d", &input);
		if(input==0){
			break;
		}
		prune(data,input,cnt);
	}
	
	
	system("pause");
	return 0;
	
}
