// Robot Gear System Optimizer - Simplified JavaScript

// Global variables
let allCombinations = [];
let currentPage = 1;
const itemsPerPage = 10;

// Initialize the application
document.addEventListener('DOMContentLoaded', function() {
    generateAllCombinations();
    setupNavigation();
    setupFilters();
    setupCalculator();
    setupRPMFinder();
    displayCombinations();
});

// Generate all 147 gear combinations
function generateAllCombinations() {
    const inputRPMs = [100, 200, 600];
    const gearSizes = [12, 24, 36, 48, 60, 72, 80];
    
    allCombinations = [];
    
    for (let rpm of inputRPMs) {
        for (let driving of gearSizes) {
            for (let driven of gearSizes) {
                const gearRatio = calculateGearRatio(driving, driven);
                const outputRPM = calculateOutputRPM(rpm, driving, driven);
                const category = getSpeedCategory(outputRPM);
                
                allCombinations.push({
                    inputRPM: rpm,
                    drivingGear: driving,
                    drivenGear: driven,
                    gearRatio: gearRatio,
                    outputRPM: outputRPM,
                    category: category
                });
            }
        }
    }
    
    // Sort by output RPM by default
    allCombinations.sort((a, b) => b.outputRPM - a.outputRPM);
}

// Calculate gear ratio
function calculateGearRatio(drivingGear, drivenGear) {
    return drivenGear / drivingGear;
}

// Calculate output RPM
function calculateOutputRPM(inputRPM, drivingGear, drivenGear) {
    const gearRatio = calculateGearRatio(drivingGear, drivenGear);
    return inputRPM / gearRatio;
}

// Get speed category
function getSpeedCategory(outputRPM) {
    if (outputRPM > 500) return 'High Speed';
    if (outputRPM > 100) return 'Medium Speed';
    return 'Low Speed';
}

// Setup navigation
function setupNavigation() {
    const navButtons = document.querySelectorAll('.nav-btn');
    const sections = document.querySelectorAll('.section');
    
    navButtons.forEach(button => {
        button.addEventListener('click', () => {
            const targetSection = button.getAttribute('data-section');
            
            // Update active button
            navButtons.forEach(btn => btn.classList.remove('active'));
            button.classList.add('active');
            
            // Show target section
            sections.forEach(section => {
                section.classList.remove('active');
                if (section.id === targetSection) {
                    section.classList.add('active');
                }
            });
        });
    });
}

// Setup filters
function setupFilters() {
    const rpmFilter = document.getElementById('rpmFilter');
    const sortFilter = document.getElementById('sortFilter');
    
    rpmFilter.addEventListener('change', filterAndDisplay);
    sortFilter.addEventListener('change', filterAndDisplay);
    
    // Setup pagination
    document.getElementById('prevPage').addEventListener('click', () => {
        if (currentPage > 1) {
            currentPage--;
            displayCombinations();
        }
    });
    
    document.getElementById('nextPage').addEventListener('click', () => {
        const totalPages = Math.ceil(allCombinations.length / itemsPerPage);
        if (currentPage < totalPages) {
            currentPage++;
            displayCombinations();
        }
    });
}

// Setup calculator
function setupCalculator() {
    const calculateBtn = document.getElementById('calculateBtn');
    calculateBtn.addEventListener('click', calculateGearSetup);
    
    // Also calculate on input changes
    document.getElementById('calcInputRPM').addEventListener('change', calculateGearSetup);
    document.getElementById('calcDrivingGear').addEventListener('change', calculateGearSetup);
    document.getElementById('calcDrivenGear').addEventListener('change', calculateGearSetup);
    
    // Initial calculation
    calculateGearSetup();
}

// Setup RPM finder
function setupRPMFinder() {
    const findOptionsBtn = document.getElementById('findOptionsBtn');
    findOptionsBtn.addEventListener('click', findRPMOptions);
    
    // Also find options when Enter is pressed
    document.getElementById('targetRPM').addEventListener('keypress', (e) => {
        if (e.key === 'Enter') {
            findRPMOptions();
        }
    });
}

// Find gear options for target RPM
function findRPMOptions() {
    const targetRPM = parseFloat(document.getElementById('targetRPM').value);
    const rpmOptionsContainer = document.getElementById('rpmOptions');
    
    if (!targetRPM || targetRPM <= 0) {
        rpmOptionsContainer.innerHTML = '<div class="no-options">Please enter a valid target RPM</div>';
        return;
    }
    
    // Find combinations that give exactly the target RPM
    const exactMatches = allCombinations.filter(combo => 
        Math.abs(combo.outputRPM - targetRPM) < 0.1
    );
    
    if (exactMatches.length === 0) {
        rpmOptionsContainer.innerHTML = '<div class="no-options">No exact matches found for ' + targetRPM + ' RPM</div>';
        return;
    }
    
    let html = '<div class="simple-list">';
    html += `<div class="list-header">Gear combinations for ${targetRPM} RPM output:</div>`;
    
    exactMatches.forEach((option, index) => {
        html += `
            <div class="list-item">
                <span class="item-number">${index + 1}.</span>
                <span class="item-input">${option.inputRPM} RPM</span>
                <span class="item-gears">${option.drivingGear}T → ${option.drivenGear}T</span>
                <span class="item-ratio">${option.gearRatio.toFixed(2)}:1</span>
                <span class="item-output">${option.outputRPM.toFixed(1)} RPM</span>
            </div>
        `;
    });
    
    html += '</div>';
    rpmOptionsContainer.innerHTML = html;
}

// Calculate gear setup
function calculateGearSetup() {
    const inputRPM = parseFloat(document.getElementById('calcInputRPM').value) || 200;
    const drivingGear = parseInt(document.getElementById('calcDrivingGear').value) || 24;
    const drivenGear = parseInt(document.getElementById('calcDrivenGear').value) || 48;
    
    const gearRatio = calculateGearRatio(drivingGear, drivenGear);
    const outputRPM = calculateOutputRPM(inputRPM, drivingGear, drivenGear);
    const speedFactor = 1 / gearRatio;
    const torqueFactor = gearRatio;
    
    // Update results
    document.getElementById('calcRatio').textContent = `${gearRatio.toFixed(2)}:1`;
    document.getElementById('calcOutput').textContent = `${outputRPM.toFixed(1)} RPM`;
    document.getElementById('calcSpeedFactor').textContent = `${speedFactor.toFixed(2)}x`;
    document.getElementById('calcTorqueFactor').textContent = `${torqueFactor.toFixed(2)}x`;
}

// Filter and display combinations
function filterAndDisplay() {
    currentPage = 1;
    displayCombinations();
}

// Display combinations with pagination
function displayCombinations() {
    const rpmFilter = document.getElementById('rpmFilter').value;
    const sortFilter = document.getElementById('sortFilter').value;
    const tbody = document.getElementById('combinationsBody');
    
    // Filter combinations
    let filteredCombinations = allCombinations.filter(combo => {
        if (rpmFilter === 'all') return true;
        return combo.inputRPM === parseInt(rpmFilter);
    });
    
    // Sort combinations
    switch (sortFilter) {
        case 'output':
            filteredCombinations.sort((a, b) => b.outputRPM - a.outputRPM);
            break;
        case 'ratio':
            filteredCombinations.sort((a, b) => b.gearRatio - a.gearRatio);
            break;
        case 'input':
            filteredCombinations.sort((a, b) => a.inputRPM - b.inputRPM);
            break;
    }
    
    // Calculate pagination
    const startIndex = (currentPage - 1) * itemsPerPage;
    const endIndex = startIndex + itemsPerPage;
    const pageCombinations = filteredCombinations.slice(startIndex, endIndex);
    const totalPages = Math.ceil(filteredCombinations.length / itemsPerPage);
    
    // Update page info
    document.getElementById('pageInfo').textContent = `Page ${currentPage} of ${totalPages}`;
    
    // Update pagination buttons
    document.getElementById('prevPage').disabled = currentPage === 1;
    document.getElementById('nextPage').disabled = currentPage === totalPages;
    
    // Clear table
    tbody.innerHTML = '';
    
    // Populate table
    pageCombinations.forEach(combo => {
        const row = document.createElement('tr');
        row.innerHTML = `
            <td>${combo.inputRPM} RPM</td>
            <td>${combo.drivingGear}T</td>
            <td>${combo.drivenGear}T</td>
            <td>${combo.gearRatio.toFixed(2)}:1</td>
            <td>${combo.outputRPM.toFixed(1)} RPM</td>
            <td><span class="category-badge ${combo.category.toLowerCase().replace(' ', '-')}">${combo.category}</span></td>
        `;
        tbody.appendChild(row);
    });
}

// Add CSS for category badges
const style = document.createElement('style');
style.textContent = `
    .category-badge {
        padding: 0.25rem 0.5rem;
        border-radius: 12px;
        font-size: 0.8rem;
        font-weight: 500;
        color: white;
    }
    
    .category-badge.high-speed {
        background: linear-gradient(90deg, #ff6b6b, #ee5a24);
    }
    
    .category-badge.medium-speed {
        background: linear-gradient(90deg, #feca57, #ff9ff3);
        color: #333;
    }
    
    .category-badge.low-speed {
        background: linear-gradient(90deg, #4834d4, #686de0);
    }
    
    button:disabled {
        opacity: 0.5;
        cursor: not-allowed;
    }
    
    button:disabled:hover {
        transform: none;
        box-shadow: none;
    }
`;
document.head.appendChild(style);
