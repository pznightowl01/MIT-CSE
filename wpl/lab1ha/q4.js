const populationData = [
    { country: "INDIA", year: 1998, population: 85 },
    { country: "INDIA", year: 1999, population: 90 },
    { country: "INDIA", year: 2000, population: 100 },

    { country: "USA", year: 1998, population: 30 },
    { country: "USA", year: 1999, population: 35 },
    { country: "USA", year: 2000, population: 40 },

    { country: "UK", year: 1998, population: 25 },
    { country: "UK", year: 1999, population: 30 },
    { country: "UK", year: 2000, population: 35 }
];

const table = document.getElementById("populationTable");

populationData.forEach(data => {
    const row = document.createElement("tr");

    row.innerHTML = `
        <td class="country">${data.country}</td>
        <td class="year">${data.year}</td>
        <td class="population">${data.population}</td>
    `;

    table.appendChild(row);
});
