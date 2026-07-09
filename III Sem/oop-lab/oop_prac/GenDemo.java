class Gen<T>{
    T ob;

    Gen(T o){
        ob = o;
    }

    T getob(){
        return ob;
    }

    void showType(){
        System.out.println("Type of T is"+ob.getClass().getName());
    }
}

class GenDemo{
    public static void main(String[] args){
        Gen<Integer> iob;
        iob=new Gen<Integer>(66);
        iob.showType();
        int v=iob.getob();
        System.out.println("Value: "+v);
        System.out.println();
        Gen<String> strob=new Gen<String>("Generics Test");
        strob.showType();
        String str = strob.getob();
        System.out.println("Value: "+str);
    }
}