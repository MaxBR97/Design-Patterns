
import java.util.*;



public class Main {

    public static void main(String[] args){
        List<Type> types = new LinkedList<>();
        types.add(new Number(3));
        types.add(new ComplexNumber(3,-1));
        types.add(new Text("Hello World "));
        List<Type> modifiedTypes = new LinkedList<>();
        for(Type t : types){
            modifiedTypes.add(t.accept(new MultiplierVisitor(),5));
        }

        for(Type t : modifiedTypes){
            System.out.println(t.toString());
        }
    }
}