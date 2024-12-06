
class MultiplierVisitor implements Visitor {
    public MultiplierVisitor (){}

    public Text visit(Text t, int times) {
        Text ans = new Text("");
        for(int i = 0; i < times; i++){
            ans.str += t.str;
        }
        return ans;
    }

    public Number visit(Number n, int times){
        Number ans = new Number(0);
        ans.value += n.value*times;
        return ans;
    }

    public ComplexNumber visit(ComplexNumber c, int times){
        ComplexNumber ans = new ComplexNumber(0,0);
        ans.real += c.real*times;
        ans.imaginary += c.imaginary*times;
        return ans;
    }

}