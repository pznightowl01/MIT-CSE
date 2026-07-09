from django.shortcuts import render, redirect
from django.views.generic import FormView
from .forms import OrderForm

PRICES = {
    'hp': {'mobile': 400, 'laptop': 900},
    'nokia': {'mobile': 300, 'laptop': 900},
    'samsung': {'mobile': 500, 'laptop': 900},
    'motorola': {'mobile': 350, 'laptop': 900},
    'apple': {'mobile': 800, 'laptop': 1200},
}

class OrderFormView(FormView):
    template_name = 'billing/order_form.html'
    form_class = OrderForm
    success_url = '/bill/'

    def form_valid(self, form):
        self.request.session['order_data'] = form.cleaned_data
        return super().form_valid(form)

def bill_view(request):
    order_data = request.session.get('order_data')
    if not order_data:
        return redirect('order_form')

    brand = order_data['brand']
    items = order_data['items']
    quantity = order_data['quantity']

    total = 0
    item_names = []
    for item in items:
        price = PRICES[brand][item]
        subtotal = price * quantity
        total += subtotal
        item_names.append(f"{item.title()} (${price} x {quantity} = ${subtotal})")

    context = {
        'brand': brand.upper(),
        'items': item_names,
        'quantity': quantity,
        'total': total,
    }
    return render(request, 'billing/bill.html', context)
