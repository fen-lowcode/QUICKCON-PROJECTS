
document.getElementById('loginForm').addEventListener('submit', async (e) => {
    e.preventDefault(); // Prevents page reload

    // Get the values from the inputs
    const firstName = document.getElementById("fname").value;
    const lastName = document.getElementById("lname").value;
    const password = document.getElementById("psw").value;

    try {
        const response = await fetch('http://192.168.1.14:2222/auth/session', {
            method: 'POST',
            headers: { 
                'Content-Type': 'application/json',
            },
            
            body: JSON.stringify({ 
                fname: firstName,
                lname: lastName,
                psw: password 
            })
        });

    
        if(!response.ok) { var data = await response.json(); alert(JSON.stringify(data))}
        if(response.ok){ 
            var data = await response.json();
            alert(JSON.stringify(data.token))
            document.cookie = "token=" + data.token + "; path=/; SameSite=Lax; Secure";
            // redirect client to data management window
            window.location.href = "./data_lookup/index.html"
        }
        

    } catch (error) {
        console.error("Failed to connect to backend:", error);
        alert("Error: Could not reach the backend server.");
    }
});
