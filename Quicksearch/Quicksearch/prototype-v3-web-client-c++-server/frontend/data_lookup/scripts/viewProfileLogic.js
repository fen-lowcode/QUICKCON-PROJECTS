
/* ============================================================
    4. EVENT HANDLING (The Bridge)
============================================================ */
document.addEventListener('click', function(e) {
    let row = e.target.closest('#tableBody tr');
    let isDelete = e.target.closest('.delete-btn');

    if (row === null || isDelete !== null) return;

    // Extracting data from table columns (Indices match <thead>)
    let cells = row.cells;
    let data = {

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

    openProfile(data);
});


// Helper to write data to the DOM. Checks if ID exists before writing.
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

function openProfile(data) {


    let profileCard = document.getElementById("profile-modal-background");
    profileCard.style.display = "flex";

    // Header logic

     // Direct Mapping to the Template IDs we created

    writeToUI('view-name',    data.CLIENTS_NAME);
    writeToUI('customer-name',data.CLIENTS_NAME);
    writeToUI('view-id',      data.ID);
    writeToUI('view-plan',    data.PLAN);
    writeToUI('view-creds',   data.CREDENTIALS);
    writeToUI('view-applied', data.DATE_APPLIED);
    writeToUI('view-age',     data.AGE);
    writeToUI('view-sex',     data.SEX);
    writeToUI('view-job',     data.OCCUPATION);
    writeToUI('view-dob',     data.DATE_OF_BIRTH);
    writeToUI('view-pob',     data.PLACE_OF_BIRTH);
    writeToUI('view-address', data.ADDRESS);
    writeToUI('view-contact', data.CONTACT_NO);
    writeToUI('view-social',  data.SOCIAL_MEDIA);
    writeToUI('view-optical', data.OPTICAL_INFO);
    writeToUI('view-tech',    data.INSTALLED_BY);
    writeToUI('view-remarks', data.REMARKS);
    writeToUI('view-sc',      data.SC_CONNECTOR);
    writeToUI('view-fiber',   data.FIBER_DROP);
    writeToUI('view-clip',    data.TAPPING_CLIP);
    writeToUI('view-tie',     data.CABLE_TIE);
    writeToUI('view-fclamp',  data.F_CLAMP);
}

function closeProfile() {
    let profileCard = document.getElementById("profile-modal-background");
    profileCard.style.display = "none";
}

function openHistory(data) {
    loadTemplates('view-payment-history')
}

