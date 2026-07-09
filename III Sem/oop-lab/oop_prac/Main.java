// import buildingPackage.Building;
// import buildingPackage.House;
// import buildingPackage.School;

public class Main {
    public static void main(String[] args) {
        Building b = new Building();
        b.assign();
        b.display();

        House h = new House();
        h.assign();
        h.display();

        School s = new School();
        s.assign();
        s.display();
    }
}
