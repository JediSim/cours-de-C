
function traiteData(json,id) {
  colors=[
    'rgba(255, 99, 132)',
    'rgba(255, 159, 64)',
    'rgba(255, 205, 86)',
    'rgba(75, 192, 192)',
    'rgba(54, 162, 235)',
    'rgba(153, 102, 255)',
    'rgba(201, 203, 207)'
  ]
    if(id=="test"){
        // Si on a appelé le chemin /q1
        document.getElementById(id).innerText = json;
    }
    else if(id=="q1"){
        // Si on a appelé le chemin /q1
        a=parseInt(json[0]["value"])
        b=parseInt(json[1]["value"])
        data = {
            labels: [
              'Donnée de test',
              'Donnée réelles'
            ],
            datasets: [{
              label: 'Personne ayant activé le mode test',
              data: [a,b],
              backgroundColor: [
                'rgb(255, 99, 132)',
                'rgb(54, 162, 235)'
                ],
              hoverOffset: 4
            }]
          };
        const myChart = new Chart(
            document.getElementById('q1'),
            {
                type:'pie',
                data:data,
            }
          );
  }
  else if(id=="q2"){
    // Si on a appelé le chemin /q2
    console.log("Prénoms : ",json)
    a=parseInt(json[0]["value"])
    b=parseInt(json[1]["value"])
    console.log(a+" - "+b)
    data = {
        labels: [
          'Case non coché',
          'Case coché'
        ],
        datasets: [{
          label: 'Personne ayant activé le mode test',
          data: [a,b],
          backgroundColor: [
            'rgb(255, 99, 132)',
            'rgb(54, 162, 235)'
            ],
          hoverOffset: 4
        }]
      };
    const myChart = new Chart(
        document.getElementById('q2'),
        {
            type:'pie',
            data:data,
        }
      );
  }
  else if (id=="q3"){
    initialesArray=[]
    dataArray=[]
    colorsArray=[]
    for (let i=0; i<json.length; i++){
      initialesArray.push(json[i]._id)
      dataArray.push(json[i].value)
      colorsArray.push(colors[Math.floor(Math.random() * colors.length)])
    }
      
    data = {
      labels: initialesArray,
      datasets: [{
        display:false,
        label: "",
        data: dataArray,
        backgroundColor: colorsArray,
        hoverOffset: 4
      }]
    };

    const myChart = new Chart(
      document.getElementById('q3'),
      {
        type: 'bar',
        data: data,
        options: {
          indexAxis: 'y',
          elements: {
            bar: {
              borderWidth: 2,
            }
          },
          responsive: true,
          plugins: {
            legend: {
              title:{
                display:false,
              },
              position: 'right',
            }
          }
        }
      }
    );
  }
  else if(id=="q4" || id=="q5"){
    labelArray=[]
    dataArray=[]
    colorsArray=[]
    for (let i=0; i<json.length; i++){
      labelArray.push(json[i]._id)
      dataArray.push(json[i].value)
      colorsArray.push(colors[Math.floor(Math.random() * colors.length)])
    }
    data = {
      labels: labelArray,
      datasets: [{
        label: 'Filière des participants',
        data: dataArray,
        backgroundColor: colorsArray,
        hoverOffset: 4
      }]
    };
  const myChart = new Chart(
      document.getElementById(id),
      {
          type:'pie',
          data:data,
      }
    );
  }
  else if(id=="q6"){
    labelArray=[]
    dataArray=[]
    colorsArray=[]
    for (let i=0; i<json.length; i++){
      labelArray.push(json[i]._id)
      dataArray.push(json[i].value)
      colorsArray.push(colors[Math.floor(Math.random() * colors.length)])
    }
    data = {
      labels: labelArray,
      datasets: [{
        label: "",
        data: dataArray,
        fill: false,
        borderColor: 'rgb(75, 192, 192)',
        tension: 0.1
      }]
    }
    const myChart = new Chart(
      document.getElementById(id),
      {
          type:'line',
          data:data,
          options:{
            scales: {
              x: {
                display: true,
                title: {
                  display: true,
                  text:"Heure d'affluence"
                }
              },
              y: {
                display: true,
                title: {
                  display: true,
                  text: 'Personnes'
                }
              }
          }
          
      }
    }
    );
  }
  else if(id=="q7"){
    if (json[0]["_id"]=="on")
      q=json[0].value
    else
      q=json[1].value
    document.getElementById(id).innerHTML=Math.round(((q*100)/(json[0].value+json[1].value))*100)/100+"% des personnes qui viennent en voiture font du covoiturage"
  }
  else if(id=="q8"){
    labelArray=[]
    dataArray=[]
    colorsArray=[]
    for (let i=0; i<json.length; i++){
      labelArray.push(json[i]._id)
      dataArray.push(json[i].value)
      colorsArray.push(colors[Math.floor(Math.random() * colors.length)])
    }
    data = {
      labels: labelArray,
      datasets: [{
        label: 'Temps passé dans les transport (en min)',
        data: dataArray,
        backgroundColor: colorsArray,
        hoverOffset: 4
      }]
    };
  const myChart = new Chart(
      document.getElementById(id),
      {
          type:'bar',
          data:data,
      }
    );
  }
}

var request = function(url, id) { 
    var xmlhttp = new XMLHttpRequest(); 
    xmlhttp.onreadystatechange = function() { 
        if (this.readyState == 4 && this.status == 200) { 
            traiteData(JSON.parse(this.responseText),id)
        } 
    }; 
    xmlhttp.open("GET", url); 
    xmlhttp.send(); 
} 


//request("./distance/chambery", "test"); 
request("./q1", "q1"); 
request("./q3","q3");
request("./q4","q4");
request("./q5","q5");
request("./q6","q6");
request("./q7","q7");
request("./q8","q8");