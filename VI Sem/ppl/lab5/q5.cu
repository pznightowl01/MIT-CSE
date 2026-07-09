//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) write a program in CUDA to sort every row of a matrix using selection sort

#include <stdio.h>

__global__ void rowsort(int *a,int r,int c){
    int row=blockIdx.x;
    if(row<r){
        for(int i=0;i<c-1;i++){
            int min=i;
            for(int j=i+1;j<c;j++)
                if(a[row*c+j]<a[row*c+min])min=j;
            int t=a[row*c+i];
            a[row*c+i]=a[row*c+min];
            a[row*c+min]=t;
        }
    }
}

int main(){
    int r,c;
    printf("rows cols: ");
    scanf("%d%d",&r,&c);

    int a[r][c];
    printf("matrix:\n");
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            scanf("%d",&a[i][j]);

    int *d;
    cudaMalloc((void**)&d,r*c*sizeof(int));
    cudaMemcpy(d,a,r*c*sizeof(int),cudaMemcpyHostToDevice);

    rowsort<<<r,1>>>(d,r,c);

    cudaMemcpy(a,d,r*c*sizeof(int),cudaMemcpyDeviceToHost);

    printf("sorted matrix:\n");
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }

    cudaFree(d);
    return 0;
}
