
/* ============================================================
    detects if a row is selected and then takes all the information in the row and send it to the profile  page
============================================================ */


// globalmvariable that contains client profile data
let clientData

document.addEventListener('click', function(e) {
    let row = e.target.closest('#tableBody tr');
    let isDelete = e.target.closest('.delete-btn');

    if (row === null || isDelete !== null) return;

    // Extracting clientData from table columns (Indices match <thead>)
    let cells = row.cells;
    clientData = {

        ID:             cells[1].innerText,  
        CLIENTS_NAME:   cells[2].innerText,
        CREDENTIALS:    cells[3].innerText,
        ADDRESS:        cells[4].innerText,
        PLAN:           cells[5].innerText,
        DATE_APPLIED:   cells[6].innerText,
        CONTACT_NO:     cells[7].innerText,
        AGE:            cells[8].innerText,
        SEX:            cells[9].innerText,
        SOCIAL_MEDIA:   cells[10].innerText,
        OCCUPATION:     cells[11].innerText,
        DATE_OF_BIRTH:  cells[12].innerText,
        PLACE_OF_BIRTH: cells[13].innerText,
        OPTICAL_INFO:   cells[14].innerText,
        SC_CONNECTOR:   cells[15].innerText,
        FIBER_DROP:     cells[16].innerText,
        TAPPING_CLIP:   cells[17].innerText,
        CABLE_TIE:      cells[18].innerText,
        F_CLAMP:        cells[19].innerText,
        REMARKS:        cells[20].innerText,
        INSTALLED_BY:   cells[21].innerText,

    };

    openProfile(clientData);
});


// Helper to write clientData to the DOM. Checks if ID exists before writing.
function writeToUI(elementId, value) {
    let target = document.getElementById(elementId);
    if (target !== null) {
        // If value is null or empty, use a placeholder
        if (value === undefined || value === null || value === "") {
            target.innerText = "---";
        } else {
            target.innerText = value;
        }
    }
}

function openProfile(clientData) {

    // sets the profile window visible
    let profileCard = document.getElementById("profile-modal-background");
    profileCard.style.display = "flex";

    // Header logic

     // Direct Mapping to the Template IDs we created

    writeToUI('view-name',    clientData.CLIENTS_NAME);
    writeToUI('customer-name',clientData.CLIENTS_NAME);
    writeToUI('view-id',      clientData.ID);
    writeToUI('view-plan',    clientData.PLAN);
    writeToUI('view-creds',   clientData.CREDENTIALS);
    writeToUI('view-applied', clientData.DATE_APPLIED);
    writeToUI('view-age',     clientData.AGE);
    writeToUI('view-sex',     clientData.SEX);
    writeToUI('view-job',     clientData.OCCUPATION);
    writeToUI('view-dob',     clientData.DATE_OF_BIRTH);
    writeToUI('view-pob',     clientData.PLACE_OF_BIRTH);
    writeToUI('view-address', clientData.ADDRESS);
    writeToUI('view-contact', clientData.CONTACT_NO);
    writeToUI('view-social',  clientData.SOCIAL_MEDIA);
    writeToUI('view-optical', clientData.OPTICAL_INFO);
    writeToUI('view-tech',    clientData.INSTALLED_BY);
    writeToUI('view-remarks', clientData.REMARKS);
    writeToUI('view-sc',      clientData.SC_CONNECTOR);
    writeToUI('view-fiber',   clientData.FIBER_DROP);
    writeToUI('view-clip',    clientData.TAPPING_CLIP);
    writeToUI('view-tie',     clientData.CABLE_TIE);
    writeToUI('view-fclamp',  clientData.F_CLAMP);
}


function closeProfile() {
    let profileCard = document.getElementById("profile-modal-background");
    // set's the profile window not visible
    profileCard.style.display = "none";
}


// the function responsible for fetching all the profile info for update request

document.getElementById('update-btn').addEventListener('click', function() {


    var takeInput = (id) => {
        const elementVal = document.getElementById(id);
        return elementVal.innerText
    }

   const s = {
        ID: clientData.ID, // Assuming ID is not editable via takeInput
        CLIENTS_NAME: takeInput('view-name'),
        PLAN: takeInput('view-plan'),
        CREDENTIALS: takeInput('view-creds'),
        DATE_APPLIED: takeInput('view-applied'),
        AGE: takeInput('view-age'),
        SEX: takeInput('view-sex'),
        OCCUPATION: takeInput('view-job'),
        DATE_OF_BIRTH: takeInput('view-dob'),
        PLACE_OF_BIRTH: takeInput('view-pob'),
        ADDRESS: takeInput('view-address'),
        CONTACT_NO: takeInput('view-contact'),
        SOCIAL_MEDIA: takeInput('view-social'),
        OPTICAL_INFO: takeInput('view-optical'),
        INSTALLED_BY: takeInput('view-tech'),
        REMARKS: takeInput('view-remarks'),
        SC_CONNECTOR: takeInput('view-sc'),
        FIBER_DROP: takeInput('view-fiber'),
        TAPPING_CLIP: takeInput('view-clip'),
        CABLE_TIE: takeInput('view-tie'),
        F_CLAMP: takeInput('view-fclamp')
    };

    console.log(JSON.stringify(s));
    updateCustomer(s);
});
