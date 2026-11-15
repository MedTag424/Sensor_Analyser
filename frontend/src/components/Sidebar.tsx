import {
  Activity,
  LayoutDashboard,
  Radio,
  Settings,
  CircleHelp,
} from "lucide-react";

export default function Sidebar() {
  return (
    <aside className="sidebar">
      <div className="brand">
        <div className="brand-icon">
          <Activity size={22} />
        </div>
        <span>Sensor<span className="brand-light">Flow</span></span>
      </div>

      <div className="sidebar-section">
        <p className="sidebar-label">MONITORING</p>

        <a className="nav-link active" href="#">
          <LayoutDashboard size={18} />
          <span>Overview</span>
        </a>

        <a className="nav-link" href="#sensors">
          <Radio size={18} />
          <span>Sensors</span>
        </a>
      </div>

      <div className="sidebar-section">
        <p className="sidebar-label">SYSTEM</p>

        <a className="nav-link" href="#">
          <Settings size={18} />
          <span>Settings</span>
        </a>

        <a className="nav-link" href="#">
          <CircleHelp size={18} />
          <span>Help & Support</span>
        </a>
      </div>

      <div className="sidebar-bottom">
        <div className="system-indicator">
          <span className="online-dot" />
          <div>
            <strong>System online</strong>
            <small>Monitoring active</small>
          </div>
        </div>
      </div>
    </aside>
  );
}
