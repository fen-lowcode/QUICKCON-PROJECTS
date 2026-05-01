
function showPaymentHistoryForm() {
    const customerForm = document.querySelector(".history-modal-overlay");
    customerForm.style.display = "flex";
}


function hidePaymentHistoryForm() {
    const customerForm = document.querySelector(".history-modal-overlay");
    customerForm.style.display = "none";
}


document.getElementById('payment-history-btn-save').addEventListener('click', function(){
    const payment_date = document.getElementById('p-date');
    const payment_amount = document.getElementById('p-amount');
    const payment_method = document.getElementById('p-method');
    const payment_note = document.getElementById('p-notes');
    const payment_for_monthof = document.getElementById('p-for-month');

    const data = {
        id: clientData.ID,
        date: payment_date.value,
        amount: payment_amount.value,
        method: payment_method.value,
        note: payment_note.value,
        month: payment_for_monthof.value
    }

    console.log(data);
    submitpaymentHistory(data);
})