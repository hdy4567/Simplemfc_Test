import React, { useEffect, useRef, useState } from 'react';

export default function PhysicsSwitcher() {
  const [activeTab, setActiveTab] = useState('wave'); // 'wave' | 'gravity' | 'magnetic'
  const canvasRef = useRef(null);

  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    const ctx = canvas.getContext('2d');
    let animationFrameId;
    let time = 0;

    // Handle mouse tracking for interactivity
    let mouse = { x: canvas.width / 2, y: canvas.height / 2, active: false };

    const handleMouseMove = (e) => {
      const rect = canvas.getBoundingClientRect();
      mouse.x = e.clientX - rect.left;
      mouse.y = e.clientY - rect.top;
    };
    
    const handleMouseEnter = () => mouse.active = true;
    const handleMouseLeave = () => mouse.active = false;

    canvas.addEventListener('mousemove', handleMouseMove);
    canvas.addEventListener('mouseenter', handleMouseEnter);
    canvas.addEventListener('mouseleave', handleMouseLeave);

    // ==========================================
    // 1. WAVE FLOW SETUP
    // ==========================================
    const rows = 20;
    const cols = 30;

    // ==========================================
    // 2. GRAVITATIONAL ORBIT SETUP
    // ==========================================
    const centralMass = { x: 300, y: 200, mass: 1500 };
    let satellites = Array.from({ length: 40 }, () => {
      const angle = Math.random() * Math.PI * 2;
      const radius = 60 + Math.random() * 120;
      // Calculate circular orbit speed: v = sqrt(G * M / r)
      const speed = Math.sqrt(1.5 * centralMass.mass / radius);
      return {
        x: centralMass.x + Math.cos(angle) * radius,
        y: centralMass.y + Math.sin(angle) * radius,
        vx: -Math.sin(angle) * speed,
        vy: Math.cos(angle) * speed,
        size: 2 + Math.random() * 3,
        color: `hsl(${180 + Math.random() * 60}, 80%, 60%)`
      };
    });

    // ==========================================
    // 3. VECTOR MAGNETIC SETUP
    // ==========================================
    const gridSpacing = 25;
    const magnets = [
      { x: 180, y: 200, strength: 4000, type: 'N', color: '#ff4d4d' }, // North (Repels/Pushes)
      { x: 420, y: 200, strength: -4000, type: 'S', color: '#3b82f6' } // South (Attracts/Pulls)
    ];

    // ==========================================
    // MAIN ANIMATION LOOP
    // ==========================================
    const render = () => {
      ctx.fillStyle = '#0f172a'; // Deep dark background
      ctx.fillRect(0, 0, canvas.width, canvas.height);
      time += 0.02;

      if (activeTab === 'wave') {
        // Wave Flow Render
        for (let r = 0; r < rows; r++) {
          for (let c = 0; c < cols; c++) {
            const x = (canvas.width / (cols - 1)) * c;
            const y = (canvas.height / (rows - 1)) * r;

            // Generate field force using multiple sine waves combined
            const waveX = Math.sin(c * 0.2 + time) * 15;
            const waveY = Math.cos(r * 0.2 + time) * 15;

            ctx.beginPath();
            ctx.arc(x + waveX, y + waveY, 2, 0, Math.PI * 2);
            ctx.fillStyle = `hsl(${200 + c * 2}, 85%, 65%)`;
            ctx.fill();
          }
        }
      } 
      
      else if (activeTab === 'gravity') {
        // Gravitational Orbit Render
        const center = mouse.active ? mouse : centralMass;

        // Draw Central Star
        ctx.beginPath();
        ctx.arc(center.x, center.y, 12, 0, Math.PI * 2);
        ctx.fillStyle = '#f59e0b';
        ctx.shadowBlur = 20;
        ctx.shadowColor = '#f59e0b';
        ctx.fill();
        ctx.shadowBlur = 0; // reset blur

        // Update & Draw Satellites
        satellites.forEach(p => {
          const dx = center.x - p.x;
          const dy = center.y - p.y;
          const distSq = dx * dx + dy * dy + 100; // soft factor to prevent infinite speed
          const dist = Math.sqrt(distSq);
          
          // Gravitational pull force formula: F = G * (m1 * m2) / r^2
          const force = (1.2 * centralMass.mass) / distSq;
          p.vx += (dx / dist) * force;
          p.vy += (dy / dist) * force;
          
          p.x += p.vx;
          p.y += p.vy;

          ctx.beginPath();
          ctx.arc(p.x, p.y, p.size, 0, Math.PI * 2);
          ctx.fillStyle = p.color;
          ctx.fill();
        });
      } 
      
      else if (activeTab === 'magnetic') {
        // Vector Magnetic Render
        // Draw Field Lines (Grid Vectors)
        for (let x = gridSpacing / 2; x < canvas.width; x += gridSpacing) {
          for (let y = gridSpacing / 2; y < canvas.height; y += gridSpacing) {
            let totalFx = 0;
            let totalFy = 0;

            magnets.forEach(m => {
              const dx = x - m.x;
              const dy = y - m.y;
              const distSq = dx * dx + dy * dy + 400;
              const dist = Math.sqrt(distSq);
              
              // Force strength degrades by distance squared
              const force = m.strength / distSq;
              totalFx += (dx / dist) * force;
              totalFy += (dy / dist) * force;
            });

            // Calculate field orientation vector angle
            const angle = Math.atan2(totalFy, totalFx);
            const vecLength = Math.min(12, Math.sqrt(totalFx * totalFx + totalFy * totalFy) * 8);

            // Draw field vector arrow pointer
            ctx.save();
            ctx.translate(x, y);
            ctx.rotate(angle);
            ctx.beginPath();
            ctx.moveTo(-vecLength / 2, 0);
            ctx.lineTo(vecLength / 2, 0);
            ctx.strokeStyle = `rgba(148, 163, 184, ${0.2 + vecLength / 12})`;
            ctx.lineWidth = 1.5;
            ctx.stroke();
            ctx.restore();
          }
        }

        // Draw Magnets
        magnets.forEach(m => {
          ctx.beginPath();
          ctx.arc(m.x, m.y, 14, 0, Math.PI * 2);
          ctx.fillStyle = m.color;
          ctx.fill();
          
          ctx.fillStyle = '#ffffff';
          ctx.font = 'bold 12px sans-serif';
          ctx.textAlign = 'center';
          ctx.textBaseline = 'middle';
          ctx.fillText(m.type, m.x, m.y);
        });
      }

      animationFrameId = requestAnimationFrame(render);
    };

    render();

    return () => {
      cancelAnimationFrame(animationFrameId);
      canvas.removeEventListener('mousemove', handleMouseMove);
      canvas.removeEventListener('mouseenter', handleMouseEnter);
      canvas.removeEventListener('mouseleave', handleMouseLeave);
    };
  }, [activeTab]);

  return (
    <div style={styles.container}>
      {/* Simulation Tab Switcher */}
      <div style={styles.tabList} role="tablist">
        <button 
          style={{ ...styles.tabButton, ...(activeTab === 'wave' ? styles.activeTab : {}) }}
          onClick={() => setActiveTab('wave')}
        >
          🌊 Wave Flow
        </button>
        <button 
          style={{ ...styles.tabButton, ...(activeTab === 'gravity' ? styles.activeTab : {}) }}
          onClick={() => setActiveTab('gravity')}
        >
          🌌 Gravity Orbit
        </button>
        <button 
          style={{ ...styles.tabButton, ...(activeTab === 'magnetic' ? styles.activeTab : {}) }}
          onClick={() => setActiveTab('magnetic')}
        >
          🧲 Vector Magnetic
        </button>
      </div>

      {/* Simulator Viewer Canvas Screen */}
      <div style={styles.canvasContainer}>
        <canvas ref={canvasRef} width={600} height={400} style={styles.canvas} />
        {activeTab === 'gravity' && (
          <div style={styles.caption}>Move your cursor inside the canvas to change gravity center!</div>
        )}
      </div>
    </div>
  );
}

// Minimalist Theme Stylesheet
const styles = {
  container: {
    width: '100%',
    maxWidth: '640px',
    backgroundColor: '#1e293b',
    borderRadius: '16px',
    padding: '16px',
    boxShadow: '0 10px 25px -5px rgba(0,0,0,0.3)',
    fontFamily: 'system-ui, sans-serif',
  },
  tabList: {
    display: 'flex',
    gap: '8px',
    marginBottom: '12px',
  },
  tabButton: {
    flex: 1,
    padding: '10px 14px',
    backgroundColor: '#334155',
    color: '#94a3b8',
    border: 'none',
    borderRadius: '8px',
    cursor: 'pointer',
    fontWeight: '600',
    fontSize: '13px',
    transition: 'all 0.2s',
  },
  activeTab: {
    backgroundColor: '#3b82f6',
    color: '#ffffff',
    boxShadow: '0 0 12px rgba(59, 130, 246, 0.4)',
  },
  canvasContainer: {
    position: 'relative',
  },
  canvas: {
    width: '100%',
    height: 'auto',
    backgroundColor: '#0f172a',
    borderRadius: '10px',
    display: 'block',
  },
  caption: {
    position: 'absolute',
    bottom: '12px',
    left: '12px',
    color: 'rgba(255,255,255,0.6)',
    fontSize: '11px',
    pointerEvents: 'none',
    backgroundColor: 'rgba(15,23,42,0.7)',
    padding: '4px 8px',
    borderRadius: '4px',
  }
};