
function showAddCustomerForm() {
    const customerForm = document.querySelector(".modal-overlay");
    customerForm.style.display = "block";
}


function hideAddCustomerForm() {
    const customerForm = document.querySelector(".modal-overlay");
    customerForm.style.display = "none";
}


function setupNewCustomer() {
    const customerData = getFormData();
    if(customerData === null) {
        console.log("Adding New Customer Has Failed"); return;
    }
    addCustomer(customerData);
}

function getFormData(){

    const allFieldIds = [ 
        'm-name', 'm-creds', 'm-address', 'm-plan', 'm-applied', 'm-contact', 'm-age', 'm-sex',
        'm-social', 'm-job','m-dob','m-pob','m-optical','m-sc', 'm-fiber', 'm-clip', 'm-tie',
        'm-fclamp', 'm-remarks', 'm-tech'
    ];

    const requiredFields = ['m-name', 'm-creds','m-address', 'm-contact', 'm-plan', 'm-applied'];
    let isInvalid = false;

    const val = (id) => {
        const el = document.getElementById(id);
        if (!el) return "N/A"; // Safety check if ID is missing in HTML

        const value = el.value.trim();

        if(requiredFields.includes(id) && value === "") {
            el.classList.add('shake-error');
            el.placeholder = "Required Field";
            isInvalid = true; 
            return null;
        }

        return value == "" ? "N/A": value;   
    }

    const data = {
        CLIENTS_NAME:   val(allFieldIds[0]),
        CREDENTIALS:    val(allFieldIds[1]),
        ADDRESS:        val(allFieldIds[2]),
        PLAN:           val(allFieldIds[3]),
        DATE_APPLIED:   val(allFieldIds[4]),
        CONTACT_NO:     val(allFieldIds[5]),
        AGE:            val(allFieldIds[6]),
        SEX:            val(allFieldIds[7]),
        SOCIAL_MEDIA:   val(allFieldIds[8]),
        OCCUPATION:     val(allFieldIds[9]),
        DATE_OF_BIRTH:  val(allFieldIds[10]),
        PLACE_OF_BIRTH: val(allFieldIds[11]),
        OPTICAL_INFO:   val(allFieldIds[12]),
        SC_CONNECTOR:   val(allFieldIds[13]),
        FIBER_DROP:     val(allFieldIds[14]),
        TAPPING_CLIP:   val(allFieldIds[15]),
        CABLE_TIE:      val(allFieldIds[16]),
        F_CLAMP:        val(allFieldIds[17]),
        REMARKS:        val(allFieldIds[18]),
        INSTALLED_BY:   val(allFieldIds[19]),
    };

    if(isInvalid === true) {
        return null;
    }

    allFieldIds.forEach(id => {
        const el = document.getElementById(id);
        el.value = "";
    })

    hideAddCustomerForm();
    return data;
}
