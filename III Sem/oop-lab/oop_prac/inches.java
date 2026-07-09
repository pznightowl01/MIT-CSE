// public class inches{
//     public static void main(String[] args){
//         long cubicinches, inchespermile;

//         //compute inches per mile
//         inchespermile =5280 * 12;

//         //compute the number of cubic inches
//         cubicinches = inchespermile * inchespermile * inchespermile;
//         System.out.println("There are "+cubicinches+" Cubic inches in a cubic mile.");
//     }
// }

public class inches{
    public static void main(String[] args){
        long inchespermile, cubicinches;
        inchespermile = 5280 * 12;
        cubicinches = inchespermile * inchespermile * inchespermile;
System.out.println("There are "+cubicinches+" Cubic inches in a cubic mile.");
    }
}