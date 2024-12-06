

class Text implements Type {
    String str;
    public Text(String s){
        str = s;
    }

    @Override
    public Type accept(Visitor v, int extraParam) {
        return v.visit(this, extraParam);
    }

    public String toString(){
        return str;
    }
}