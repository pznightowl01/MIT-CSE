// class prac{
//     static void genException(){
//         int nums[] = new int[4];
//         System.out.println("Before exception is generated.");
//         System.out.println();
//         nums[7] = 10;
//         System.out.println("This won't be displayed");
//         System.out.println();
//     }
// }

// class prac2{
//     public static void main(String[] args){
//         int nums[] = new int[4];
//         try{
//             prac.genException();
//         }
//         catch(ArrayIndexOutOfBoundsException exc){
//             System.out.println("Index out-of-bounds!");
//             System.out.println();
//         }
//         System.out.println("After catch statement.");
//         System.out.println();
//     }
// }

class prac{
    static void genException(){
        int nums[] = new int[4];
        System.out.println("Before exception is generated.");
        nums[7]=10;
        System.out.println("this won't be displayed.");
    }
}

class prac2{
    public static void main(String args[]){
        try{
            prac.genException();
        }
        catch(ArrayIndexOutOfBoundsException exc){
            System.out.println("Index-out-of-bounds!");
        }
        System.out.println("After catch statement");
    }
}