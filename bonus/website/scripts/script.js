document.querySelectorAll('nav ul li a').forEach(link => {
    link.addEventListener('click', function(event) {
        event.preventDefault();

        const targetId = this.getAttribute('href').substring(1);
        document.getElementById(targetId).scrollIntoView({ behavior: 'smooth' });

        document.querySelector('nav ul li a.active').classList.remove('active');
        this.classList.add('active');
    });
});

window.addEventListener('scroll', function() {
    const sections = document.querySelectorAll('.content');
    let currentSection = '';

    sections.forEach(section => {
        const sectionTop = section.offsetTop;
        const sectionHeight = section.clientHeight;
        if (pageYOffset >= sectionTop - sectionHeight / 3) {
            currentSection = section.getAttribute('id');
        }
    });

    document.querySelectorAll('nav ul li a').forEach(link => {
        link.classList.remove('active');
        if (link.getAttribute('href').substring(1) === currentSection) {
            link.classList.add('active');
        }
    });
});

function spawnCloud() {
    const cloud = document.createElement('div');
    cloud.classList.add('cloud');
    
    const fromLeft = Math.random() < 0.5;
    const minTop = 50;
    const maxTop = window.innerHeight - 60;
    const randomTop = Math.random() * (maxTop - minTop) + minTop;
    
    cloud.style.top = randomTop + 'px';
    if (fromLeft) {
        cloud.style.left = '-100px';
        cloud.style.animationName = 'moveCloudsLeft';
    } else {
        cloud.style.left = 'calc(100vw + 100px)';
        cloud.style.animationName = 'moveCloudsRight';
    }

    document.querySelector('.background').appendChild(cloud);

    setTimeout(() => {
        cloud.remove();
    }, 15000);
}

setInterval(spawnCloud, 5000);
spawnCloud();
