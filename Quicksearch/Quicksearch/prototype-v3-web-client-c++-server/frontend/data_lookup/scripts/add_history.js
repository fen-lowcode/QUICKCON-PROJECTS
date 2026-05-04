
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
        ID: clientData.ID,
        PAYMENT_DATE: payment_date.value,
        AMOUNT_PAID: payment_amount.value,
        PAYMENT_METHOD: payment_method.value,
        NOTES: payment_note.value,
        PAYMENT_FOR_MONTHOF: payment_for_monthof.value
    }
   
    submitpaymentHistory(data);

    payment_date.value = ""
    payment_amount.value = ""
    payment_method.value = ""
    payment_note.value = ""
    payment_for_monthof.value = ""
    getPaymentHistory(clientData.ID);
    hidePaymentHistoryForm();
})

